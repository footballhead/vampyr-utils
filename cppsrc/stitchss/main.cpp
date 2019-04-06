#include <vampyrutils/image.hpp>

#include <iostream>
#include <stdexcept>

using namespace vampyrutils;

namespace {

struct cmdline_input {
    char const* output;
    std::vector<char const*> input;

    static cmdline_input parse(int argc, char** argv) {
        if (argc < 4) {
            throw std::invalid_argument{"Need at least 3 args!"};
        }

        std::vector<char const*> inputs{};
        inputs.reserve(argc - 2);
        for (int i = 2; i < argc; ++i) {
            inputs.push_back(argv[i]);
        }

        return {argv[1], inputs};
    }
};

std::vector<image> load_all_images(std::vector<char const*> const& files)
{
    auto images = std::vector<image>{};
    images.reserve(files.size());

    for (auto const& file : files) {
        images.push_back(image::from_file(file));
    }

    return images;
}

} // namespace

int main(int argc, char** argv)
{
    try {
        auto const args = cmdline_input::parse(argc, argv);

        try {
            auto const images = load_all_images(args.input);

            auto sprite_sheet = images[0];
            for (size_t i = 1; i < images.size(); ++i) {
                sprite_sheet = sprite_sheet.stitch(images[i]);
            }

            sprite_sheet.save(args.output);
        } catch (std::exception const& e) {
            std::cerr << e.what() << "\n";
        }
    } catch(std::invalid_argument const& e) {
        std::cerr << e.what() << "\n";
        std::cerr << "Usage: stitchss OUTPUT.BMP FILE1.BMP FILE2.BMP [FILE3.BMP ...]\n";
        return 1;
    }

    return 0;
}
