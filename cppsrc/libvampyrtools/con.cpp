#include "con.hpp"

#include <fstream>

namespace {

using namespace vampyrtools;

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

void save_data(std::vector<char> const& data, char const* file)
{
    auto out = std::ofstream{file, std::ios_base::binary};
    if (out.fail()) {
        throw std::runtime_error{"Failed to open output file"};
    }

    out.write(data.data(), data.size());
    if (!out.good()) {
        throw std::runtime_error{"Failed to write output file"};
    }
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

std::vector<char> decolorize(image const& img, std::function<char(color const&)> ega_fn)
{
    auto ega_data = std::vector<char>{};
    ega_data.reserve(img.width * img.height);

    for (auto const& c : img.data) {
        ega_data.push_back(ega_fn(c));
    }

    return ega_data;
}

} // namespace

namespace vampyrtools {

image load_con(char const* file, int width, int height, palette const& pal)
{
    if (width <= 0) {
        throw std::invalid_argument{"Expected positive width"};
    }

    if (height <= 0) {
        throw std::invalid_argument{"Expected positive height"};
    }

    auto const raw_data = read_input(file, width * height);
    // Dimensions are reversed because the file is stored transposed and we want to untranspose it
    auto const data = transpose(raw_data, height, width);
    return image{width, height, colorize(data, pal)};
}

void save_as_con(image const& img, char const* file, std::function<char(color const&)> ega_fn)
{
    if (img.width <= 0) {
        throw std::invalid_argument{"Expected positive width"};
    }

    if (img.height <= 0) {
        throw std::invalid_argument{"Expected positive height"};
    }

    if (img.data.size() != img.width * img.height) {
        throw std::invalid_argument{"Not enough color data to fill dimensions"};
    }

    auto const ega_data = decolorize(img, ega_fn);
    auto const ega_data_t = transpose(ega_data, img.width, img.height);
    save_data(ega_data_t, file);
}

} // namespace vampyrtools
