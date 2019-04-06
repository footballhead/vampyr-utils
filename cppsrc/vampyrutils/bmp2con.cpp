#include "bmp2con.hpp"

#include "io.hpp"

namespace {

using namespace vampyrutils;

std::vector<char> decolorize(std::vector<color> const& img, std::function<char(color const&)> ega_fn)
{
    auto ega_data = std::vector<char>{};
    ega_data.reserve(img.size());

    for (auto const& c : img) {
        ega_data.push_back(ega_fn(c));
    }

    return ega_data;
}

} // namespace

namespace vampyrutils {

void bmp2con(image const& img, char const* file, std::function<char(color const&)> ega_fn)
{
    auto const ega_data = array2d<char>{img.get_bounds(), decolorize(img.data.data, ega_fn)};
    save_data(ega_data.transpose().data, file);
}

} // namespace vampyrutils
