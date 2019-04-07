#include <vampyrutils/csv.hpp>
#include <vampyrutils/image.hpp>

#include <iostream>

using namespace vampyrutils;

namespace {

inline point operator*(extent const& e, point const& p)
{
	return {e.w * p.x, e.h * p.y};
}

inline point operator*(point const& p, extent const& e)
{
	return {e.w * p.x, e.h * p.y};
}


inline point operator-(point const& a, point const& b)
{
	return {a.x - b.x, a.y - b.y};
}

constexpr size_t enconter_num_columns = 7;

std::vector<image> split_horizontally(image const& sheet)
{
	auto const sprite_bounds = extent{sheet.get_bounds().h, sheet.get_bounds().h};
	return sheet.split(sprite_bounds);
}

struct enconter_row {
	int icon;
	point location;
};

struct cmdline_input {
    char const* input;
    char const* enconter;
    int begin;
    int end;
    char const* spritesheet;
    char const* output;

    static cmdline_input parse(int argc, char** argv) {
        if (argc != 7) {
            throw std::invalid_argument{"Invalid number of command-line arguments"};
        }

        auto const begin = std::stoi(argv[3]);
        if (begin < 0) {
            throw std::invalid_argument{"Expected positive integer beginning offset"};
        }

        auto const end = std::stoi(argv[4]);
        if (end < 0) {
            throw std::invalid_argument{"Expected positive integer end offset"};
        }

        return cmdline_input{argv[1], argv[2], begin, end, argv[5], argv[6]};
    }
};

} // namespace

int main(int argc, char** argv)
{
	try {
        auto const args = cmdline_input::parse(argc, argv);

        try {
        	auto map_img = image::from_file(args.input);
            auto const table = csv_table<enconter_num_columns>::from_file(args.enconter).sub(args.begin, args.end);
            auto const sprites = split_horizontally(image::from_file(args.spritesheet));

            for (auto const& row : table.rows) {
            	auto const f_row = enconter_row{std::stoi(row[0]),
            		point{std::stoi(row[3]), std::stoi(row[4])} - point{1, 1}};

            	auto const& sprite = sprites[f_row.icon];
            	map_img.blit(sprite, f_row.location * sprite.get_bounds());
            }

            map_img.save(args.output);
        } catch (std::runtime_error const& e) {
            std::cerr << e.what() << '\n';
            return 1;
        }
    } catch (std::invalid_argument const& e) {
        std::cerr << e.what() << '\n';
        std::cerr << "Usage: map_layer_enconter INPUT.MAP ENCONTER.CSV BEGIN END MON.BMP OUTPUT.MAP\n";
        return 1;
    }

    return 0;
}