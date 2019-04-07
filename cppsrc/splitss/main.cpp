#include <vampyrutils/image.hpp>

#include <filesystem>
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace vampyrutils;

namespace {

struct cmdline_input {
    char const* input;
    extent bounds;
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

        return cmdline_input{argv[1], {width, height}, argv[4]};
    }
};

} // namespace

int main(int argc, char** argv) {
    try {
        auto const args = cmdline_input::parse(argc, argv);

        try {
            if (!std::filesystem::exists(args.outdir)) {
                if (!std::filesystem::create_directories(args.outdir)) {
                    std::cerr << "Could not make out dir: " << args.outdir << "\n";
                    return 1;
                }
            }

            auto const subimages = image::from_file(args.input).split(args.bounds);

            for (size_t i = 0; i < subimages.size(); ++i) {
                auto outfile = std::ostringstream{};
                outfile << args.outdir << "/" << i << ".bmp";
                subimages[i].save(outfile.str().c_str());
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