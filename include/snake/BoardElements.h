#pragma once

#include "nana/paint/graphics.hpp"

#include "snake/GraphicsBoard.h"

#include "snake/Types.h"
#include "snake/utils.h"

namespace snake {

class BasicSnake {
 public:
    BasicSnake() {}

    void setInitialPosition(const Point& head_, const Point& tail_) {
        if (head_.x < 0 || head_.y < 0 || tail_.x < 0 || tail_.y < 0) {
            throw std::runtime_error("Bad values: BasicSnake does not support negativ coordinates.");
        }

        head = head_;
        tail = tail_;
    }

    void drawInitialSnake(GraphicsBoard& board) {
        if (board.getHeight() >= std::max(head.x, tail.x) || board.getWidth() >= std::max(head.y, tail.y)) {
            throw std::runtime_error("Cannot draw snake: BasicSnake does not support overflowing coordinates.");
        }

        Point current = head;
        board.getPixel(head).set(BoardPixel::State::SNAKE);
        while (current != tail) {
            current = incrementPointTowardsPoint(current, tail);
            board.getPixel(current).set(BoardPixel::State::SNAKE);
        }
    }

 private:
    Point head {};
    Point tail {};
};

}