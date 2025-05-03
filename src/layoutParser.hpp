#pragma once

#include <functional>
#include <string>
#include <vector>
#include <json.hpp>
#include "property.hpp"
#include "windowSettings.hpp"
#include "key.hpp"
using json = nlohmann::json;

class LayoutParser {
private:
	json data;
	Rect getRect(const json& data);
	Color getColor(const json& data);

public:
	json parse();
	WindowSettings loadWindowSettings();
	std::unordered_map<uint16_t, Key> loadKeys();
};