#pragma once

#include <functional>
#include <vector>

namespace vampyrutils {

struct point {
    int x = 0;
    int y = 0;
};

inline point operator+(point const& a, point const& b)
{
    return {a.x + b.x, a.y + b.y};
}

struct extent {
    int w = 0;
    int h = 0;

    int area() const {
        return w * h;
    }

    int index(point const& p) const {
        return p.y * w + p.x;
    }

    extent transpose() const {
        return {h, w};
    }

    void foreach(std::function<void(point const&)> fn) const {
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                fn({x, y});
            }
        }
    }
};

struct rectangle {
    point p;
    extent bounds;

    int area() const {
        return bounds.area();
    }

    void foreach(std::function<void(point const&)> fn) const {
        bounds.foreach([this, &fn](point const& pnt) {
            fn(this->p + pnt);
        });
    }
};

template <typename T>
struct array2d {
    extent bounds;
    std::vector<T> data;

    T get(point const& p) const {
        return data[bounds.index(p)];
    }

    void set(const T& c, point const& p) {
        data[bounds.index(p)] = c;
    }

    void foreach(std::function<void(point const&, T)> fn) const {
        bounds.foreach([this, &fn](point const& p) {
            fn(p, get(p));
        });
    }

    array2d<T> transpose() const {
        auto transposed = array2d{bounds.transpose(), {}};
        transposed.data.reserve(data.size());

        for (int x = 0; x < bounds.w; ++x) {
            for (int y = 0; y < bounds.h; ++y) {
                transposed.data.push_back(data[bounds.index({x, y})]);
            }
        }

        return transposed;
    }

};

} // namespace std
