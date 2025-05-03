#pragma once

#include <cstdint>
#include <string>
#include "graphicsTypes.hpp"

struct WindowSettings {
	uint16_t width;
	uint16_t height;
	Color backgroundColor;
	std::string fontPath;
	uint16_t fontSize = 32;
};