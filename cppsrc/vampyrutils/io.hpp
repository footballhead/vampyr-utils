#pragma once

#include <vector>

namespace vampyrutils {

std::vector<char> load_data(char const* file, int count);

void save_data(std::vector<char> const& data, char const* file);

} // namespace vampyrutils
