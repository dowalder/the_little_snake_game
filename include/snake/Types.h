namespace snake {
struct Point {
    int x = 0;
    int y = 0;

    bool operator==(const Point& other) {
        return x == other.x && y == other.y;
    }
    bool operator!=(const Point& other) {
        return !(*this == other);
    }
};


}