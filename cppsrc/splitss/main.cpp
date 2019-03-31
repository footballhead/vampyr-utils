#include <libvampyrtools/image.hpp>

#include <filesystem>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace vampyrtools;

namespace {

struct cmdline_input {
    char const* input;
    int width;
    int height;
    char const* outdir;

    static cmdline_input parse(int argc, char** argv) {
        if (argc != 5) {
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

        return cmdline_input{argv[1], width, height, argv[4]};
    }
};

} // namespace

int main(int argc, char** argv) {
    try {
        auto const args = cmdline_input::parse(argc, argv);

        try {
            if (!std::filesystem::create_directories(args.outdir)) {
                std::cerr << "Could not make out dir: " << args.outdir << "\n";
                return 1;
            }
            auto const img = image::from_file(args.input);

            for (int y = 0; y < img.height / args.height; y++) {
                for (int x = 0; x < img.width / args.width; x++) {
                    auto const subimg = img.sub({x * args.width, y * args.width, args.width, args.height});

                    auto outfile = std::ostringstream{};
                    outfile << args.outdir << "/" << x << "-" << y << ".bmp";
                    subimg.save(outfile.str().c_str());
                }
            }
            
        } catch (std::runtime_error const& e) {
            std::cerr << e.what() << "\n";
            return 1;
        }
    } catch (std::invalid_argument const& e) {
        std::cerr << e.what() << "\n";
        std::cerr << "Usage: splitss BMPFILE WIDTH HEIGHT OUTDIR\n";
        return 1;
    }

    return 0;
}