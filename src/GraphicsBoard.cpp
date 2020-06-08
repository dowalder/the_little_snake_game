#include "snake/GraphicsBoard.h"

namespace snake {

nana::color BoardTile::foregroundColor(nana::colors::azure);
nana::color BoardTile::backgroundColor(nana::colors::black);

BoardTile::BoardTile(int locationX_, int locationY_) 
:   startX {locationX_ * pixelSize}, 
    startY {locationY_ * pixelSize},
    myRectangle{startX, startY, pixelSize, pixelSize}
{}

void BoardTile::set(State newState) {
    state = newState;
}

BoardTile::State BoardTile::getState() const { return state; }

void BoardTile::draw(nana::paint::graphics& graph) {
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

void BoardTile::drawBackground(nana::paint::graphics& graph) {
    graph.rectangle(myRectangle, true, backgroundColor);
}

void BoardTile::drawSnake(nana::paint::graphics& graph) {
    graph.rectangle(myRectangle, true, foregroundColor);
}

void BoardTile::drawFood(nana::paint::graphics& graph) {
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

BoardTile& GraphicsBoard::getTile(const Point& p) {
    return pixels.at(p.x * height + p.y);
}

const BoardTile& GraphicsBoard::getTile(const Point& p) const {
    return pixels.at(p.x * height + p.y);
}

void GraphicsBoard::update() const {
    drawing.update();
}

void GraphicsBoard::createPixels() {
    graphics.resize({width * BoardTile::pixelSize, height * BoardTile::pixelSize});
    pixels.clear();
    pixels.reserve(height * width);
    for (int h = 0; h < height; ++h) {
        for (int w = 0; w < width; ++w) {
            pixels.emplace_back(h, w);
        }
    }
}



    
} // namespace snake

