#pragma once

#include "nana/gui.hpp"

#include "snake/GraphicsBoard.h"
#include "snake/BoardElements.h"

namespace snake {
    

class MainWindow {
  public:
    MainWindow() : board {mainForm} {
        mainForm.caption("Goold Old Snake");

        mainForm.show();
    }

  private:
    nana::form mainForm;

    GraphicsBoard board;
    BasicSnake snake;
};

}