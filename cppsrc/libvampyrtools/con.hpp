#pragma once

#include "image.hpp"

#include <functional>

namespace vampyrtools {

image load_con(char const* file, int width, int height, palette const& pal = ega_palette);

void save_as_con(image const& img, char const* file, std::function<char(color const&)> ega_fn = color_to_ega);

} // namespace vampyrtools
