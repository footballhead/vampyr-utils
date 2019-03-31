#include <libvampyrtools/con.hpp>
#include <libvampyrtools/stb_image_write.h>

#include <fstream>
#include <iostream>
#include <string>

namespace {

struct cmdline_args {
    char* input;
    int width;
    int height;
    char* output;

    static cmdline_args parse(int argc, char** argv) {
        if (argc != 5) {
            throw std::invalid_argument{"Invalid number of command-line arguments"};
        }

        auto const width = std::stoi(argv[2]);
        if (width <= 0) {
            throw std::invalid_argument{"Expected positive width"};
        }

        auto const height = std::stoi(argv[3]);
        if (height <= 0) {
            throw std::invalid_argument{"Expected positive height"};
        }

        return cmdline_args{argv[1], width, height, argv[4]};
    };
};

bool save_image(vampyrtools::image const& img, char const* file)
{
    auto constexpr rgb_comp = 3;
    return stbi_write_bmp(file, img.width, img.height, rgb_comp, img.data.data()) != 0;
}

}

int main(int argc, char** argv)
{
    auto args = cmdline_args{};
    try {
        args = cmdline_args::parse(argc, argv);

        auto const image = vampyrtools::load_con(args.input, args.width, args.height);
        auto const result = save_image(image, args.output);
        if (result == 0) {
            std::cerr << "Failed to write output " << args.output << "\n";
            return 1;
        }
    } catch (std::exception const& e) {
        std::cerr << e.what() << "\n";
        std::cerr << "Usage: con2bmp INPUT.CON WIDTH HEIGHT OUTPUT.BMP\n";
        return 1;
    }

    return 0;
}
