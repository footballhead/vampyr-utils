#pragma once

#include "image.hpp"

#include <functional>

namespace vampyrutils {

void bmp2con(image const& img, char const* file, std::function<char(color const&)> ega_fn = color_to_ega);

} // namespace vampyrutils
