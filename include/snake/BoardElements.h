#pragma once
/*
This files provides classes for the elements that are found on a snake board. Currently, that is only 
the snake itself.
*/

#include <deque>
#include <queue>

#include "nana/paint/graphics.hpp"

#include "snake/GraphicsBoard.h"

#include "snake/Types.h"

namespace snake {

/**
 * The BasicSnake is the simplest snake possible in snake: it fails if it runs into anything
 * on the board other than food and it is always consecutive on the board. Extensions are possible; the
 * interface of this BasicSnake can also support more complex variants (like ones that can move into walls 
 * and teleport to the other side of the board).
*/
class BasicSnake {
 public:
    BasicSnake() = default;

    /* The snake will fill itself in between the head and the tail. */
    void setInitialPosition(const Point& head, const Point& tail);

    /* Copy the snake to the board. */
    void initSnakeOnBoard(GraphicsBoard& board) const;

    /**
     * The main function that gets called repeadetly during the game. Since it takes a mutable reference to the board it 
     * has full authority about how it interacts with the board. This means the snake can have arbitrary powers, e.g. it
     * could search for the food in the board and teleport itself directly their. This makes this step function a core 
     * function in the game and in a more elaborate design I assume that this responsibility would be moved out of the 
     * snake.
    */
    StepResult step(Direction dir, GraphicsBoard& board);

    const Point& head() const;
    const Point& tail() const;

 private:
    /* This class exists for easy extensibilty: different bodyparts might look different in future implementations.*/
    class BodyPart {
      public:
        BodyPart(const Point& position) : pos {position} {}

        const Point pos;
    };

    struct GraphicsUpdate {
        Point where;
        BoardTile::State what;
    };

    std::deque<BodyPart> bodyParts;

    bool validStepTarget(const GraphicsBoard& board, Point target);
};

}