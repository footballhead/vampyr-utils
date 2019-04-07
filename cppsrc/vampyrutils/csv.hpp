#pragma once

#include <algorithm>
#include <array>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace vampyrutils {

namespace detail {

std::vector<std::string> split_string(std::string const& s)
{
	auto cells = std::vector<std::string>{};

	size_t after_last_tab = 0;
	while (true) {
		auto tab_pos = s.find('\t', after_last_tab);
		if (tab_pos == std::string::npos) {
			break;
		}

		cells.push_back(s.substr(after_last_tab, tab_pos - after_last_tab));
		after_last_tab = tab_pos + 1;
	}

	// Account from last tab up until newline
	cells.push_back(s.substr(after_last_tab));

	return cells;
}

} // namespace detail

template <size_t columns>
using csv_row = std::array<std::string, columns>;

template <int columns>
struct csv_table {
	std::vector<csv_row<columns>> rows;

	static csv_table<columns> from_file(char const* filename) {
		using namespace std::string_literals;

		std::ifstream in{filename};
		if (in.fail()) {
			throw std::runtime_error{"Failed to open: "s + filename};
		}

		auto table = csv_table<columns>{};

		auto line = ""s;
		while (std::getline(in, line).good()) {
			auto const cells = detail::split_string(line);
			if (cells.size() != columns) {
				throw std::runtime_error{"Line has wrong number of cells: "s + line};
			}

			auto row = csv_row<columns>{};
			std::copy(begin(cells), begin(cells) + columns, begin(row));
			table.rows.push_back(row);
		}

		return table;
	}

	csv_table<columns> sub(size_t begin_offset, size_t end_offset) const {
		if (begin_offset >= rows.size() || end_offset >= rows.size()) {
			throw std::invalid_argument{"Offsets exceed table size"};
		}

		return csv_table<columns>{std::vector<csv_row<columns>>(
			begin(rows) + begin_offset, begin(rows) + end_offset + 1)};
	}
};

} // namespace vampyrutils
