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

void image::blit(image const& img, point const& p)
{
    img.data.foreach([this, &p](point const& i, color const& c) {
        set(c, p + i);
    });
}

void image::save(char const* file) const
{
    auto const result = stbi_write_bmp(file, get_bounds().w, get_bounds().h, STBI_rgb, get_data().data());
    if (result == 0) {
        throw std::runtime_error{"Failed to save image"};
    }
}

} // namespace vampyrutils
