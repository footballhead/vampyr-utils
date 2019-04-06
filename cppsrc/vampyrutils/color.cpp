#include "color.hpp"

#include <sstream>
#include <unordered_map>

namespace vampyrutils {

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
        auto ss = std::ostringstream{};
        ss << "Invalid EGA color: " << c;
        throw std::invalid_argument{ss.str()};
    }
    return reverse_palette.at(c);
}

} // namespace vampyrutils
