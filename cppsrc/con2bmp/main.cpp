#include <libvampyrtools/con.hpp>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

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

}

int main(int argc, char** argv)
{
    auto args = cmdline_args{};
    try {
        args = cmdline_args::parse(argc, argv);

        auto const image = load_con(args.input, args.width, args.height);
        auto constexpr rgb_comp = 3;
        auto const result = stbi_write_bmp(args.output, args.width, args.height, rgb_comp, image.data());
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
