#include "snake/Types.h"

namespace snake {

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

Point incrementPointTowardsPoint(const Point& from, const Point& to) {
    if (from.x != to.x) {
        return {from.x + sgn(to.x - from.x), from.y};
    } else {
        return {from.y, from.y + sgn(to.y - from.y)};
    }
}

}