#include "nana/gui.hpp"

#include "snake/GraphicsBoard.h"

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
};

}