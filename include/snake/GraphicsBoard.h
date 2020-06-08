 #pragma once

 /* Definition of the main board where the game is rendered. */

#include "nana/gui.hpp"
#include "nana/paint/graphics.hpp"

#include "snake/Types.h"

namespace snake {

/* A tile on the board. A tile is the smallest element possible (e.g. one part of the snake or a small food element). */
class BoardTile {
  public:
    BoardTile(int locationX_, int locationY_);

    enum class State {
        SNAKE,
        FOOD,
        EMPTY
    };

    void set(State newState);

    State getState() const;

    /* A tile draws itself in the graph. This works currently because very little elements exist. A better 
      implementation would allow to export this drawing function to another class. This would allow that 
      e.g. the snake can draw itself. I consider this important because otherwise this class needs to have
      global knowledge of all possible things that can be drawn.
    */
    void draw(nana::paint::graphics& graph);

    /* Colors can be changed globally from everyone (static and public). This can or cannot be an issue, it depends
      a bit on the threading model and the update function which draws the pixels. Both are internal to nana and I 
      do not know enough about them to make a better statement about it.
    */
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

/* The main board that holds all tiles and nana objects that can draw the game.  */
class GraphicsBoard {
  public:
    GraphicsBoard(nana::window handle);

    BoardTile& getTile(const Point& p);
    const BoardTile& getTile(const Point& p) const;

    void update() const;

    int getWidth() const { return width; }
    int getHeight() const { return height; }

  private:
    const int height = 20;
    const int width = 20;

    nana::paint::graphics graphics;
    nana::drawing drawing;

    std::vector<BoardTile> pixels;

    void createPixels();
};



}