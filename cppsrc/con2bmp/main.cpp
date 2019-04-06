#include <vampyrutils/con2bmp.hpp>

#include <iostream>

using namespace vampyrutils;

namespace {

struct cmdline_args {
    char const* input;
    extent bounds;
    char const* output;

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

        return cmdline_args{argv[1], {width, height}, argv[4]};
    };
};

}

int main(int argc, char** argv)
{
    try {
        auto const args = cmdline_args::parse(argc, argv);
        try {
            con2bmp(args.input, args.bounds).save(args.output);
        } catch (std::runtime_error const& e) {
            std::cerr << e.what() << "\n";
            return 1;
        }
    } catch (std::invalid_argument const& e) {
        std::cerr << e.what() << "\n";
        std::cerr << "Usage: con2bmp INPUT.CON WIDTH HEIGHT OUTPUT.BMP\n";
        return 1;
    }

    return 0;
}
