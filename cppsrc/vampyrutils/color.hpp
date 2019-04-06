#pragma once

#include <array>
#include <ostream>
#include <stdexcept>

namespace vampyrutils {

struct color {
    uint8_t r = 0x00;
    uint8_t g = 0x00;
    uint8_t b = 0x00;

    bool operator==(color const& other) const {
        return r == other.r && g == other.g && b == other.b;
    }
};

inline std::ostream& operator<<(std::ostream& os, color const& c)
{
    os << "color{" << static_cast<int>(c.r) << ", " << static_cast<int>(c.g) << ", " << static_cast<int>(c.b) << "}";
    return os;
}

struct palette {
    std::array<color, 16> colors;

    color get(char i) const {
        if (static_cast<decltype(colors)::size_type>(i) >= colors.size() || i < 0) {
            throw std::invalid_argument{"Bad palette index"};
        }
        return colors[i];
    }
};

auto constexpr ega_palette = palette{{
    color{0x00, 0x00, 0x00},
    color{0x00, 0x00, 0xAA},
    color{0x00, 0xAA, 0x00},
    color{0x00, 0xAA, 0xAA},
    color{0xAA, 0x00, 0x00},
    color{0xAA, 0x00, 0xAA},
    color{0xAA, 0x55, 0x00},
    color{0xAA, 0xAA, 0xAA},
    color{0x55, 0x55, 0x55},
    color{0x55, 0x55, 0xFF},
    color{0x55, 0xFF, 0x55},
    color{0x55, 0xFF, 0xFF},
    color{0xFF, 0x55, 0x55},
    color{0xFF, 0x55, 0xFF},
    color{0xFF, 0xFF, 0x55},
    color{0xFF, 0xFF, 0xFF}
}};

char color_to_ega(color const& c);

} // namespace vampyrutils

namespace std {

template <>
struct hash<vampyrutils::color> {
    size_t operator()(vampyrutils::color const& c) const {
        return c.r << 16 | c.g << 8 | c.b;
    }
};

} // namespace std
