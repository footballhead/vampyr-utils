#pragma once

#include "image.hpp"

namespace vampyrutils {

image con2bmp(char const* file, extent const& bounds, palette const& pal = ega_palette);

} // namespace vampyrutils
