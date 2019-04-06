#include "image.hpp"

#include "stb_image.h"
#include "stb_image_write.h"

#include <sstream>
#include <stdexcept>

namespace vampyrutils {

image image::from_file(char const* file)
{
    auto bounds = extent{};
    int channels = 0;
    auto const raw_image_data = stbi_load(file, &bounds.w, &bounds.h, &channels, STBI_rgb);
    if (!raw_image_data) {
        std::ostringstream ss{};
        ss << stbi_failure_reason() << " (" << file << ")";
        throw std::runtime_error{ss.str()};
    }

    auto img = image{array2d<color>{bounds, {}}};
    img.get_data().reserve(bounds.area());
    for (auto i = 0; i < bounds.area(); ++i) {
        img.get_data().push_back(color{raw_image_data[i*3], raw_image_data[i*3+1], raw_image_data[i*3+2]});
    }

    return img;
}

image image::from_black(extent const& bounds)
{
    return image{array2d<color>{bounds, std::vector<color>(bounds.area(), color{})}};
}

image image::sub(rectangle const& rect) const
{
    auto img = image{array2d<color>{rect.bounds, {}}};
    img.get_data().reserve(rect.area());

    rect.foreach([this, &img, &rect](point const& i) {
        img.get_data().push_back(get(i));
    });

    return img;
}

image image::stitch(image const& other) const
{
    auto const bounds = extent{
        get_bounds().w + other.get_bounds().w,
        std::max(get_bounds().h, other.get_bounds().h)};
    auto sprite_sheet = image::from_black(bounds);
    sprite_sheet.blit(*this, {0, 0});
    sprite_sheet.blit(other, {get_bounds().w, 0});
    return sprite_sheet;
}

std::vector<image> image::split(extent const& tile_bounds) const
{
    auto images = std::vector<image>{};

    auto const num_rows = get_bounds().h / tile_bounds.h;
    auto const num_cols = get_bounds().w / tile_bounds.w;
    images.reserve(num_rows * num_cols);

    for (int y = 0; y < num_rows; y++) {
        for (int x = 0; x < num_cols; x++) {
            auto const sub_bounds = rectangle{x * tile_bounds.w, y * tile_bounds.h, tile_bounds};
            images.push_back(sub(sub_bounds));
        }
    }

    return images;
}

void image::save(char const* file) const
{
    auto const result = stbi_write_bmp(file, get_bounds().w, get_bounds().h, STBI_rgb, get_data().data());
    if (result == 0) {
        throw std::runtime_error{"Failed to save image"};
    }
}

void image::blit(image const& img, point const& p)
{
    img.data.foreach([this, &p](point const& i, color const& c) {
        set(c, p + i);
    });
}

} // namespace vampyrutils
