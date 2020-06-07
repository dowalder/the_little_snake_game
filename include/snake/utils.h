#pragma once
#include "snake/Types.h"
#include "snake/GraphicsBoard.h"

namespace snake {

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

Point incrementPointTowardsPoint(const Point& from, const Point& to) {
    if (from.x != to.x) {
        return {from.x + sgn(to.x - from.x), from.y};
    } else {
        return {from.x, from.y + sgn(to.y - from.y)};
    }
}

Point incrementPointWithStep(const Point& from, Direction stepDirection) {
    switch (stepDirection) {
        case Direction::LEFT:
            return {from.x - 1, from.y};
        case Direction::RIGHT:
            return {from.x + 1, from.y};
        case Direction::BOTTOM:
            return {from.x, from.y + 1};
        case Direction::TOP:
            return {from.x, from.y - 1};
        default:
            throw std::runtime_error("Unexpected direction.");
    }
}

bool pointInBoard(const GraphicsBoard& board, const Point& p) {
    return 0 < p.x && p.x < board.getWidth() && 0 < p.y && p.y < board.getHeight();
}

}