#pragma once

#include <cstdint>
#include <string>
#include "property.hpp"
#include "graphicsTypes.hpp"

struct Key {
	Property<Rect> rect;
	Property<Color> backgroundColor;
	Property<std::string> labelContent = {" ", " "};
	Property<Color> labelColor;
};