#pragma once

#include <optional>
#include <random>

#include "snake/GraphicsBoard.h"

namespace snake {

std::optional<Point> sampleEmptyPixel(const GraphicsBoard& board) {
    std::vector<Point> emptyPixels;
    for (int x = 0; x < board.getWidth(); ++x) {
        for (int y = 0; y < board.getHeight(); ++y) {
            if (board.getPixel({x, y}).getState() == BoardPixel::State::EMPTY) {
                emptyPixels.emplace_back(x, y);
            }
        }
    }
    if (emptyPixels.empty()) {
        return std::optional<Point>();
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, emptyPixels.size() - 1);
    return emptyPixels.at(distrib(gen));
}


}