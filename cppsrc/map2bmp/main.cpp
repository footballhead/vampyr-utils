#include <vampyrutils/image.hpp>
#include <vampyrutils/io.hpp>

#include <iostream>
#include <stdexcept>
#include <string>

using namespace std::string_literals;
using namespace vampyrutils;

namespace {

constexpr auto tile_size = extent{18, 18}; // DEBUG!

inline extent operator*(extent const& a, extent const& b)
{
	return {a.w * b.w, a.h * b.h};
}

inline point operator*(extent const& e, point const& p)
{
	return {e.w * p.x, e.h * p.y};
}

struct cmdline_input {
    char const* input;
    extent bounds;
    char const* tilesheet;
    char const* output;

    static cmdline_input parse(int argc, char** argv) {
        if (argc != 6) {
            throw std::invalid_argument{"Invalid number of command-line arguments"};
        }

        auto const width = std::stoi(argv[2]);
        if (width <= 0) {
            throw std::invalid_argument{"Expected positive integer width"};
        }

        auto const height = std::stoi(argv[3]);
        if (height <= 0) {
            throw std::invalid_argument{"Expected positive integer height"};
        }

        return cmdline_input{argv[1], {width, height}, argv[4], argv[5]};
    }
};

} // namespace

int main(int argc, char** argv)
{
    try {
        auto const args = cmdline_input::parse(argc, argv);

        try {
            auto const map_data_t = array2d<char>{args.bounds.transpose(), load_data(args.input, args.bounds.area())};
            auto const map_data = map_data_t.transpose();

            auto const images = image::from_file(args.tilesheet).split(tile_size);

        	auto map_img = image::from_black(args.bounds * tile_size);
            map_data.foreach([&map_img, &images](point const& p, char const& tile) {
                map_img.blit(images[tile], tile_size * p);
            });
            map_img.save(args.output);
        } catch (std::runtime_error const& e) {
            std::cerr << e.what() << "\n";
            return 1;
        }
    } catch (std::invalid_argument const& e) {
        std::cerr << e.what() << "\n";
        std::cerr << "Usage: map2bmp INPUT.MAP WIDTH HEIGHT TILESHEET.BMP OUTPUT.BMP\n";
        return 1;
    }

    return 0;
}
