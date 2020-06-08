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
        board.getPixel(part.pos).set(BoardPixel::State::SNAKE);
    }
}

StepResult BasicSnake::step(Direction dir, GraphicsBoard& board) {
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

const Point& BasicSnake::head() const { return bodyParts.front().pos; }
const Point& BasicSnake::tail() const { return bodyParts.back().pos; }

bool BasicSnake::validStepTarget(const GraphicsBoard& board, Point target) {
    return pointInBoard(board, target) && 
        (board.getPixel(target).getState() == BoardPixel::State::EMPTY 
        || board.getPixel(target).getState() == BoardPixel::State::FOOD);
}

}