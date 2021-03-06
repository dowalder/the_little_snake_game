#include "snake/BoardElements.h"

#include "snake/utils.h"

namespace snake {

void BasicSnake::setInitialPosition(const Point& head, const Point& tail) {
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

void BasicSnake::initSnakeOnBoard(GraphicsBoard& board) const {
    if (!pointInBoard(board, head()) || !pointInBoard(board, tail())) {
        throw std::runtime_error("Cannot draw snake: BasicSnake does not support overflowing coordinates.");
    }

    for (const auto& part: bodyParts) {
        board.getTile(part.pos).set(BoardTile::State::SNAKE);
    }
}

StepResult BasicSnake::step(Direction dir, GraphicsBoard& board) {
    bodyParts.emplace_front(incrementPointWithStep(head(), dir));

    if (!validStepTarget(board, head())) {
        return StepResult::INVALID_STEP;
    }

    BoardTile::State oldState = board.getTile(head()).getState();

    board.getTile(head()).set(BoardTile::State::SNAKE);

    if (oldState == BoardTile::State::FOOD) {
        return StepResult::STEPPED_INTO_FOOD;
    } else {
        // only remove the tail when no food was consumed
        board.getTile(tail()).set(BoardTile::State::EMPTY);
        bodyParts.pop_back();
        return StepResult::STEPPED_INTO_EMPTY;
    }
}

const Point& BasicSnake::head() const { return bodyParts.front().pos; }
const Point& BasicSnake::tail() const { return bodyParts.back().pos; }

bool BasicSnake::validStepTarget(const GraphicsBoard& board, Point target) {
    return pointInBoard(board, target) && 
        (board.getTile(target).getState() == BoardTile::State::EMPTY 
        || board.getTile(target).getState() == BoardTile::State::FOOD);
}

}