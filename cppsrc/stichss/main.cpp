#include <libvampyrtools/image.hpp>

#include <iostream>
#include <stdexcept>
#include <vector>

using namespace vampyrtools;

namespace {

struct cmdline_input {
    char const* output;
    std::vector<char const*> input;

    static cmdline_input parse(int argc, char** argv) {
        if (argc < 3) {
            throw std::invalid_argument{"Need at least 2 args!"};
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

dimension determine_sprite_sheet_dimensions(std::vector<image> const& images)
{
    dimension dim{0, 0};
    for (auto const& img : images) {
        dim.w += img.width;
        dim.h = std::max(dim.h, img.height);
    }

    return dim;
}

} // namespace

int main(int argc, char** argv)
{
    try {
        auto const args = cmdline_input::parse(argc, argv);

        try {
            auto const images = load_all_images(args.input);

            auto const dim = determine_sprite_sheet_dimensions(images);
            auto sprite_sheet = image::from_black(dim);

            auto p = point{0, 0};
            for (auto const& img : images) {
                sprite_sheet.blit(img, p);
                p.x += img.width;
            }

            sprite_sheet.save(args.output);
        } catch (std::exception const& e) {
            std::cerr << e.what() << std::endl;
        }
    } catch(std::invalid_argument const& e) {
        std::cerr << e.what() << "\n";
        std::cerr << "Usage: stitchss OUTPUT.BMP FILE1.BMP [FILE2.BMP ...]\n";
        return 1;
    }

    return 0;
}
