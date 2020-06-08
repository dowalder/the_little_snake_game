#pragma once

#include <optional>

#include "snake/GraphicsBoard.h"

namespace snake {

std::optional<Point> sampleEmptyPixel(const GraphicsBoard& board);

}