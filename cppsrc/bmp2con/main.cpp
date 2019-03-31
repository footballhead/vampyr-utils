#include <libvampyrtools/con.hpp>
#include <stb/stb_image.h>

#include <fstream>
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

} // namespace

int main(int argc, char** argv)
{
	try {
		auto const args = cmdline_input::parse(argc, argv);

		try {
			auto const img = load_bmp(args.input);
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
