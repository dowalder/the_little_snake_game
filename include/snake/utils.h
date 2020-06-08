#pragma once
#include "snake/Types.h"
#include "snake/GraphicsBoard.h"

namespace snake {

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

Point incrementPointTowardsPoint(const Point& from, const Point& to);

Point incrementPointWithStep(const Point& from, Direction stepDirection);

bool pointInBoard(const GraphicsBoard& board, const Point& p);

bool directionsAreOpposite(Direction dir1, Direction dir2);

}