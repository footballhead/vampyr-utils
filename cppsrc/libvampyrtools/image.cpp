#include "image.hpp"

#include "stb_image.h"
#include "stb_image_write.h"

#include <sstream>
#include <stdexcept>
#include <unordered_map>

namespace vampyrtools {

char color_to_ega(color const& c)
{
    static auto reverse_palette = std::unordered_map<color, char>{
        {color{0x00, 0x00, 0x00}, 0},
        {color{0x00, 0x00, 0xAA}, 1},
        {color{0x00, 0xAA, 0x00}, 2},
        {color{0x00, 0xAA, 0xAA}, 3},
        {color{0xAA, 0x00, 0x00}, 4},
        {color{0xAA, 0x00, 0xAA}, 5},
        {color{0xAA, 0x55, 0x00}, 6},
        {color{0xAA, 0xAA, 0xAA}, 7},
        {color{0x55, 0x55, 0x55}, 8},
        {color{0x55, 0x55, 0xFF}, 9},
        {color{0x55, 0xFF, 0x55}, 10},
        {color{0x55, 0xFF, 0xFF}, 11},
        {color{0xFF, 0x55, 0x55}, 12},
        {color{0xFF, 0x55, 0xFF}, 13},
        {color{0xFF, 0xFF, 0x55}, 14},
        {color{0xFF, 0xFF, 0xFF}, 15},
    };
    if (reverse_palette.find(c) == end(reverse_palette)) {
        auto ss = std::stringstream{};
        ss << "Invalid EGA color: ";
        ss << static_cast<int>(c.r);
        ss << ", " << static_cast<int>(c.g);
        ss << ", " << static_cast<int>(c.b);
        throw std::invalid_argument{ss.str()};
    }
    return reverse_palette.at(c);
}

image image::sub(rectangle const& rect) const
{
    auto data = std::vector<color>{};
    data.reserve(rect.w * rect.h);

    for (int y = 0; y < rect.h; ++y) {
        for (int x = 0; x < rect.w; ++x) {
            data.push_back(get(x + rect.x, y + rect.y));
        }
    }

    return {rect.w, rect.h, data};
}

image image::from_file(char const* file)
{
    int x = 0;
    int y = 0;
    int channels = 0;
    auto const raw_image_data = stbi_load(file, &x, &y, &channels, STBI_rgb);
    if (!raw_image_data) {
        throw std::runtime_error{stbi_failure_reason()};
    }

    auto image_data = std::vector<color>{};
    image_data.reserve(x*y);
    for (auto i = 0; i < x*y; ++i) {
        image_data.push_back(color{raw_image_data[i*3], raw_image_data[i*3+1], raw_image_data[i*3+2]});
    }

    return image{x, y, image_data};
}

void image::save(char const* file) const
{
    auto const result = stbi_write_bmp(file, width, height, STBI_rgb, data.data());
    if (result == 0) {
        throw std::runtime_error{"Failed to save image"};
    }
}

} // namespace vampyrtools
