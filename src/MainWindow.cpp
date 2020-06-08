#include "snake/MainWindow.h"

#include "snake/utils.h"

namespace snake {

MainWindow::MainWindow() : layout {mainForm}, mainLoop {samplingTime}, board {mainForm} {
    setupMainform();

    mainLoop.elapse([this]{ performStep(); });
    mainLoop.start();
}

void MainWindow::performStep(){
    if (state == State::CONFIGURATION) {
        lastUpdate = std::chrono::system_clock::now();
    } else if (state == State::SNAKE_STARTING) {
        setupInitialSnake();
        state = State::SNAKE_ACTIVE;
        lastUpdate = std::chrono::system_clock::now();
        board.update();
    } else if (std::chrono::system_clock::now() - lastUpdate > conf.stepDuration) {
        StepResult res = snake.step(nextDirection, board);
        lastDirection = nextDirection;

        if (res == StepResult::INVALID_STEP) {
            state = State::CONFIGURATION;
        } else if (res == StepResult::STEPPED_INTO_FOOD) {
            std::optional<Point> foodLocation = sampleEmptyPixel(board);
            if (foodLocation.has_value()) {
                board.getTile(*foodLocation).set(BoardTile::State::FOOD);
            } else {
                state = State::CONFIGURATION;
            }
        }
        lastUpdate = std::chrono::system_clock::now();
        board.update();
    }
}

void MainWindow::setupMainform(){
    mainForm.caption("A good old SNAKE game.");
    mainForm.events().key_press([this](const nana::arg_keyboard& key){
        onKeyPress(key);
    });

    mainForm.show();
}

void MainWindow::onKeyPress(const nana::arg_keyboard& key) {
    if (state == State::CONFIGURATION) {
        return;
    }

    Direction newDirection {};

    switch (key.key) {
        case 65: // a
        case 37: // left arrow
            newDirection = Direction::LEFT;
            break;
        case 87: // w
        case 38: // up arrow
            newDirection = Direction::UP;
            break;
        case 68: // d
        case 39: // right arrow
            newDirection = Direction::RIGHT;
            break;
        case 83: //s 
        case 40: // down arrow
            newDirection = Direction::DOWN;
            break;
        case 27: // escape
            state = State::CONFIGURATION;
            return;
        default:
            break;
    }
    if (!directionsAreOpposite(newDirection, lastDirection)) {
        nextDirection = newDirection;
    }
}

void MainWindow::setupInitialSnake() {
        snake.setInitialPosition(conf.initialHead, conf.initialTail);
        snake.initSnakeOnBoard(board);
        nextDirection = conf.initialDirection;
        lastDirection = conf.initialDirection;

        std::optional<Point> foodLocation = sampleEmptyPixel(board);

        if (foodLocation.has_value()) {
            board.getTile(*foodLocation).set(BoardTile::State::FOOD);
        } else {
            throw std::runtime_error("No empty tile left at start.");
        }
    }

}