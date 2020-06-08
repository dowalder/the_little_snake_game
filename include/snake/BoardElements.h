#pragma once

#include <deque>
#include <queue>

#include "nana/paint/graphics.hpp"

#include "snake/GraphicsBoard.h"

#include "snake/Types.h"

namespace snake {

class BasicSnake {
 public:
    BasicSnake() = default;

    void setInitialPosition(const Point& head, const Point& tail);

    void initSnakeOnBoard(GraphicsBoard& board) const;

    StepResult step(Direction dir, GraphicsBoard& board);

    const Point& head() const;
    const Point& tail() const;

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

    std::deque<BodyPart> bodyParts;

    bool validStepTarget(const GraphicsBoard& board, Point target);
};

}