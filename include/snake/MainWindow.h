#pragma once

#include <chrono>
#include <optional>

#include "nana/gui.hpp"
#include "nana/gui/timer.hpp"

#include "snake/GraphicsBoard.h"
#include "snake/BoardElements.h"
#include "snake/sampling.h"

namespace snake {

struct Configuration {
    std::chrono::milliseconds stepDuration {500};

    Point initialHead {0, 5};
    Point initialTail {0, 0};
    Direction initialDirection {Direction::DOWN};
};
    
/* The main application window that combines the different elements and owns the event loop. */
class MainWindow {
  public:
    MainWindow();

  private:
    enum class State {
        SNAKE_STARTING,
        SNAKE_ACTIVE,
        CONFIGURATION,  // Configuration state is planned but not implemented yet.
    } state {State::SNAKE_STARTING};
    
    static constexpr std::chrono::milliseconds samplingTime {5};

    nana::form mainForm;
    nana::place layout;
    nana::timer mainLoop;

    GraphicsBoard board;
    BasicSnake snake;

    Configuration conf;

    std::chrono::system_clock::time_point lastUpdate {};
    Direction nextDirection {Direction::DOWN};
    Direction lastDirection;

    /* The function to be called repeadetely by the nana timer. */
    void performStep();
    void onKeyPress(const nana::arg_keyboard& key);

    void setupMainform();
    void setupInitialSnake();
};

}