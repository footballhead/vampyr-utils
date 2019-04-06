#pragma once

#include "color.hpp"
#include "math.hpp"

namespace vampyrutils {

struct image {
    array2d<color> data;

    static image from_file(char const* file);
    static image from_black(extent const& bounds);

    color get(point const& p) const { return data.get(p); }
    void set(const color& c, point const& p) { data.set(c, p); }

    extent get_bounds() const { return data.bounds; }
    std::vector<color> const& get_data() const { return data.data; }
    std::vector<color>& get_data() { return data.data; }

    image sub(rectangle const& rect) const;
    void save(char const* file) const;

    void blit(image const& img, point const& p);
};

} // namespace vampyrutils
