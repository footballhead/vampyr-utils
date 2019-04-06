#include <vampyrutils/bmp2con.hpp>

#include <iostream>
#include <stdexcept>

using namespace vampyrutils;

namespace {

struct cmdline_input {
    char const* input;
    char const* output;

    static cmdline_input parse(int argc, char** argv) {
        if (argc != 3) {
            throw std::invalid_argument{"Invalid number of command-line arguments"};
        }

        return {argv[1], argv[2]};
    }
};

} // namespace

int main(int argc, char** argv)
{
    try {
        auto const args = cmdline_input::parse(argc, argv);

        try {
            bmp2con(image::from_file(args.input), args.output);
        } catch (std::runtime_error const& e) {
            std::cerr << e.what() << "\n";
        }
    } catch (std::invalid_argument const& e) {
        std::cerr << e.what() << "\n";
        std::cerr << "Usage: bmp2con INPUT.BMP OUTPUT.CON\n";
        return 1;
    }

    return 0;
}
