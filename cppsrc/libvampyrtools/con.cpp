#include "con.hpp"

#include <fstream>

namespace {

std::vector<char> read_input(char const* file, int count)
{
    auto in = std::ifstream{file, std::ios_base::in | std::ios_base::binary};
    if (in.fail()) {
        throw std::runtime_error{"Failed to open input file"};
    }

    auto data = std::vector<char>(count, 0);
    in.read(data.data(), count);
    if (!in.good()) {
        throw std::runtime_error{"Failed to read input file"};
    }

    return data;
}

std::vector<char> transpose(std::vector<char> const& data, int width, int height)
{
    auto transposed = std::vector<char>();
    transposed.reserve(data.size());

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            transposed.push_back(data[y * width + x]);
        }
    }

    return transposed;
}

std::vector<color> colorize(std::vector<char> const& data, palette const& pal)
{
    auto image = std::vector<color>{};
    image.reserve(data.size());

    for (auto const& raw_pixel : data) {
        image.push_back(pal.get(raw_pixel));
    }

    return image;
}

}

std::vector<color> load_con(char const* file, int width, int height, palette const& pal)
{
    if (width <= 0) {
        throw std::invalid_argument{"Expected positive width"};
    }

    if (height <= 0) {
        throw std::invalid_argument{"Expected positive height"};
    }

    auto const raw_data = read_input(file, width * height);
    auto const data = transpose(raw_data, height, width);
    return colorize(data, pal);
}
