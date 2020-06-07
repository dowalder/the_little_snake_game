#pragma once

namespace snake {
struct Point {
    int x = 0;
    int y = 0;

    Point() = default;
    Point(int x_, int y_) : x{x_}, y{y_} {}

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
    bool operator!=(const Point& other) const {
        return !(*this == other);
    }
};


}