#include "con2bmp.hpp"

#include "io.hpp"

#include <stdexcept>

namespace {

using namespace vampyrutils;

std::vector<color> colorize(std::vector<char> const& data, palette const& pal)
{
    auto image = std::vector<color>{};
    image.reserve(data.size());

    for (auto const& raw_pixel : data) {
        image.push_back(pal.get(raw_pixel));
    }

    return image;
}

} // namespace

namespace vampyrutils {

image con2bmp(char const* file, extent const& bounds, palette const& pal)
{
	// Dimensions are reversed because the file is stored transposed and we want to untranspose it
    auto const raw_arr = array2d<char>{bounds.transpose(), load_data(file, bounds.area())};
    auto const arr = raw_arr.transpose();
    return image{array2d<color>{bounds, colorize(arr.data, pal)}};
}


} // namespace vampyrutils
