#include "snake/GraphicsBoard.h"

namespace snake {

nana::color BoardPixel::foregroundColor(nana::colors::azure);
nana::color BoardPixel::backgroundColor(nana::colors::black);

BoardPixel::BoardPixel(int locationX_, int locationY_) 
:   startX {locationX_ * pixelSize}, 
    startY {locationY_ * pixelSize},
    myRectangle{startX, startY, pixelSize, pixelSize}
{}

void BoardPixel::set(State newState) {
    state = newState;
}

BoardPixel::State BoardPixel::getState() const { return state; }

void BoardPixel::draw(nana::paint::graphics& graph) {
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

void BoardPixel::drawBackground(nana::paint::graphics& graph) {
    graph.rectangle(myRectangle, true, backgroundColor);
}

void BoardPixel::drawSnake(nana::paint::graphics& graph) {
    graph.rectangle(myRectangle, true, foregroundColor);
}

void BoardPixel::drawFood(nana::paint::graphics& graph) {
    graph.rectangle(myRectangle, true, foregroundColor);
}

GraphicsBoard::GraphicsBoard(nana::window handle) : drawing {handle} {
    createPixels();
    
    drawing.draw([this](nana::paint::graphics& graph) {
        for (auto& pixel : pixels) {
            pixel.draw(graph);
        }
    });
}

BoardPixel& GraphicsBoard::getPixel(const Point& p) {
    return pixels.at(p.x * height + p.y);
}

const BoardPixel& GraphicsBoard::getPixel(const Point& p) const {
    return pixels.at(p.x * height + p.y);
}

void GraphicsBoard::update() const {
    drawing.update();
}

void GraphicsBoard::createPixels() {
    graphics.resize({width * BoardPixel::pixelSize, height * BoardPixel::pixelSize});
    pixels.clear();
    pixels.reserve(height * width);
    for (int h = 0; h < height; ++h) {
        for (int w = 0; w < width; ++w) {
            pixels.emplace_back(h, w);
        }
    }
}



    
} // namespace snake

