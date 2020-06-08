 #pragma once

#include "nana/gui.hpp"
#include "nana/paint/graphics.hpp"

#include "snake/Types.h"

namespace snake {

class BoardPixel {
  public:
    BoardPixel(int locationX_, int locationY_);

    enum class State {
        SNAKE,
        FOOD,
        EMPTY
    };

    void set(State newState);

    State getState() const;

    void draw(nana::paint::graphics& graph);

    static nana::color foregroundColor;
    static nana::color backgroundColor;
    static const int pixelSize = 25;

  private:
    State state = State::EMPTY;
    const int startX = 0;
    const int startY = 0;
    nana::rectangle myRectangle;

    void drawBackground(nana::paint::graphics& graph);
    void drawSnake(nana::paint::graphics& graph);
    void drawFood(nana::paint::graphics& graph);
};


class GraphicsBoard {
  public:
    GraphicsBoard(nana::window handle);

    BoardPixel& getPixel(const Point& p);
    const BoardPixel& getPixel(const Point& p) const;

    void update() const;

    int getWidth() const { return width; }
    int getHeight() const { return height; }

  private:
    const int height = 20;
    const int width = 20;

    nana::paint::graphics graphics;
    nana::drawing drawing;

    std::vector<BoardPixel> pixels;

    void createPixels();
};



}