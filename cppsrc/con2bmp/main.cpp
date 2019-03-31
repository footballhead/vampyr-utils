#include <libvampyrtools/con.hpp>

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
    try {
        auto const args = cmdline_args::parse(argc, argv);

        auto const image = vampyrtools::load_con(args.input, args.width, args.height);
        image.save(args.output);
    } catch (std::exception const& e) {
        std::cerr << e.what() << "\n";
        std::cerr << "Usage: con2bmp INPUT.CON WIDTH HEIGHT OUTPUT.BMP\n";
        return 1;
    }

    return 0;
}
