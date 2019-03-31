#include <libvampyrtools/image.hpp>
#include <libvampyrtools/stb_image.h>
#include <libvampyrtools/stb_image_write.h>

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

image load_bmp(char const* file)
{
	int x = 0;
	int y = 0;
	int channels = 0;
	auto const raw_image_data = stbi_load(file, &x, &y, &channels, STBI_rgb);
	if (!raw_image_data) {
		throw std::runtime_error{stbi_failure_reason()};
	}

	auto image_data = std::vector<color>{};
	image_data.reserve(x*y);
	for (auto i = 0; i < x*y; ++i) {
		image_data.push_back(color{raw_image_data[i*3], raw_image_data[i*3+1], raw_image_data[i*3+2]});
	}

	return image{x, y, image_data};
}

void save_bmp(vampyrtools::image const& img, char const* file)
{
    auto const result = stbi_write_bmp(file, img.width, img.height, STBI_rgb, img.data.data());
    if (result == 0) {
    	throw std::runtime_error{"Failed to save image"};
    }
}

} // namespace

int main(int argc, char** argv) {
	try {
		auto const args = cmdline_input::parse(argc, argv);

		try {
			if (!std::filesystem::create_directories(args.outdir)) {
				std::cerr << "Could not make out dir: " << args.outdir << "\n";
				return 1;
			}
			auto const img = load_bmp(args.input);

			for (int y = 0; y < img.height / args.height; y++) {
				for (int x = 0; x < img.width / args.width; x++) {
					auto const subimg = img.sub({x * args.width, y * args.width, args.width, args.height});

					auto outfile = std::ostringstream{};
					outfile << args.outdir << "/" << x << "-" << y << ".bmp";
					save_bmp(subimg, outfile.str().c_str());
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