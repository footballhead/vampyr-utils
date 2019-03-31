#include <libvampyrtools/con.hpp>

#include <iostream>
#include <stdexcept>

using namespace std::string_literals;
using namespace vampyrtools;

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
            auto const img = image::from_file(args.input);
            save_as_con(img, args.output);
        } catch (std::exception const& e) {
            std::cerr << e.what() << std::endl;
        }
    } catch(...) {
        std::cerr << "Usage: bmp2con BMPFILE CONFILE\n";
        return 1;
    }

    return 0;
}
