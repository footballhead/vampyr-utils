#include "io.hpp"

#include <fstream>
#include <stdexcept>
#include <string>

using namespace std::string_literals;

namespace vampyrutils {

std::vector<char> load_data(char const* file, int count)
{
    auto in = std::ifstream{file, std::ios_base::binary};
    if (in.fail()) {
        throw std::runtime_error{"Failed to open input file: "s + file};
    }

    auto data = std::vector<char>(count, 0);
    in.read(data.data(), count);
    if (!in.good()) {
        throw std::runtime_error{"Failed to read input file: "s + file};
    }

    return data;
}

void save_data(std::vector<char> const& data, char const* file)
{
    auto out = std::ofstream{file, std::ios_base::binary};
    if (out.fail()) {
        throw std::runtime_error{"Failed to open output file: "s + file};
    }

    out.write(data.data(), data.size());
    if (!out.good()) {
        throw std::runtime_error{"Failed to write output file: "s + file};
    }
}

} // namespace vampyrutils
