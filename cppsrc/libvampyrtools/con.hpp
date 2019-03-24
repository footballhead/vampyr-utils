#pragma once

#include <array>
#include <stdexcept>
#include <vector>

struct color {
    uint8_t r = 0x00;
    uint8_t g = 0x00;
    uint8_t b = 0x00;
};

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

std::vector<color> load_con(char const* file, int width, int height, palette const& pal = ega_palette);
