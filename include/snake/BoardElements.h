#pragma once

#include <deque>
#include <queue>

#include "nana/paint/graphics.hpp"

#include "snake/GraphicsBoard.h"

#include "snake/Types.h"
#include "snake/utils.h"

namespace snake {

class BasicSnake {
 public:
    BasicSnake() {}

    void setInitialPosition(const Point& head, const Point& tail) {
        if (head.x < 0 || head.y < 0 || tail.x < 0 || tail.y < 0) {
            throw std::runtime_error("Bad values: BasicSnake does not support negativ coordinates.");
        }
        bodyParts.clear();
        bodyParts.emplace_back(head);

        Point current = head;
        while (current != tail) {
            current = incrementPointTowardsPoint(current, tail);
            bodyParts.emplace_back(current);
        }
    }

    void initSnakeOnBoard(GraphicsBoard& board) const {
        if (!pointInBoard(board, head()) || !pointInBoard(board, tail())) {
            throw std::runtime_error("Cannot draw snake: BasicSnake does not support overflowing coordinates.");
        }

        for (const auto& part: bodyParts) {
            board.getPixel(part.pos).set(BoardPixel::State::SNAKE);
        }
    }

    StepResult step(Direction dir, GraphicsBoard& board) {
        bodyParts.emplace_front(incrementPointWithStep(head(), dir));

        if (!validStepTarget(board, head())) {
            return StepResult::INVALID_STEP;
        }

        BoardPixel::State oldState = board.getPixel(head()).getState();

        board.getPixel(head()).set(BoardPixel::State::SNAKE);

        if (oldState == BoardPixel::State::FOOD) {
            return StepResult::STEPPED_INTO_FOOD;
        } else {
            // only remove the tail when no food was consumed
            board.getPixel(tail()).set(BoardPixel::State::EMPTY);
            bodyParts.pop_back();
            return StepResult::STEPPED_INTO_EMPTY;
        }
    }

    const Point& head() const { return bodyParts.front().pos; }
    const Point& tail() const { return bodyParts.back().pos; }

 private:
    class BodyPart {
      public:
        BodyPart(const Point& position) : pos {position} {}

        const Point pos;
    };

    struct GraphicsUpdate {
        Point where;
        BoardPixel::State what;
    };

    // Changes to the snake are queued up here and can then later be written to the state.
    std::queue<GraphicsUpdate> graphicUpdates;
    std::deque<BodyPart> bodyParts;

    bool validStepTarget(const GraphicsBoard& board, Point target) {
        return pointInBoard(board, target) && 
            (board.getPixel(target).getState() == BoardPixel::State::EMPTY 
            || board.getPixel(target).getState() == BoardPixel::State::FOOD);
    }
};

}