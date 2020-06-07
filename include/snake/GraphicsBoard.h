 #pragma once

#include <iostream>

#include "nana/gui.hpp"
#include "nana/paint/graphics.hpp"

#include "snake/Types.h"

namespace snake {

class BoardPixel {
  public:
    BoardPixel(int locationX_, int locationY_) 
    :   startX {locationX_ * pixelSize}, 
        startY {locationY_ * pixelSize},
        myRectangle{startX, startY, pixelSize, pixelSize}
    {}

    enum class State {
        SNAKE,
        FOOD,
        EMPTY
    };

    void set(State newState) {
        state = newState;
    }

    void draw(nana::paint::graphics& graph) {

        switch (state) {
            case State::EMPTY:
                drawBackground(graph);
                break;
            case State::FOOD:
                drawFood(graph);
                break;
            case State::SNAKE:
                drawSnake(graph);
                break;
            default:
                throw std::runtime_error("Invalid state of Boardpixel.");
        }
    }

    // void drawConsumedFood() {}
    // void drawLargeFood()

    static nana::color foregroundColor;
    static nana::color backgroundColor;
    static const int pixelSize = 25;

  private:
    State state = State::EMPTY;
    const int startX = 0;
    const int startY = 0;
    nana::rectangle myRectangle;

    void drawBackground(nana::paint::graphics& graph) {
        graph.rectangle(myRectangle, true, backgroundColor);
    }

    void drawSnake(nana::paint::graphics& graph) {
        graph.rectangle(myRectangle, true, foregroundColor);
    }

    void drawFood(nana::paint::graphics& graph) {
        graph.rectangle(myRectangle, true, foregroundColor);
    }
};

nana::color BoardPixel::foregroundColor(nana::colors::azure);
nana::color BoardPixel::backgroundColor(nana::colors::black);


class GraphicsBoard {
  public:
    GraphicsBoard(nana::window handle) : drawing {handle} {
        createPixels();
        
        drawing.draw([this](nana::paint::graphics& graph) {
            for (auto& pixel : pixels) {
                pixel.draw(graph);
            }
        });
    }

    BoardPixel& getPixel(const Point& p) {
        return pixels.at(p.x * height + p.y);
    }

    int getWidth() const { return width; }
    int getHeight() const { return height; }

  private:
    int height = 25;
    int width = 25;

    nana::paint::graphics graphics;
    nana::drawing drawing;

    void createPixels() {
        graphics.resize({width * BoardPixel::pixelSize, height * BoardPixel::pixelSize});
        pixels.clear();
        pixels.reserve(height * width);
        for (int h = 0; h < height; ++h) {
            for (int w = 0; w < width; ++w) {
                pixels.emplace_back(h, w);
            }
        }
    }

    std::vector<BoardPixel> pixels;
};



}