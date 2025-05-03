#include "layoutParser.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include "graphicsTypes.hpp"

Rect LayoutParser::getRect(const json& data) {
	return Rect {data[0], data[1], data[2], data[3]};
};

Color LayoutParser::getColor(const json& data) {
	return Color {data[0], data[1], data[2]};
};	

json LayoutParser::parse() {
	std::string filePath;
	std::cout << "overlay file path:";
	std::cin >> filePath;

	std::ifstream file(filePath);
	if (!file.is_open())
		throw std::runtime_error("File couldn't be opened.");

	data = json::parse(file);
	file.close();

	return data;
}

WindowSettings LayoutParser::loadWindowSettings() {
	if (!data.contains("window"))
		throw std::runtime_error("'window' is required.");	
	const json windowData = data["window"];

	WindowSettings windowSettings;
	if (!windowData.contains("size"))
		throw std::runtime_error("'size' is required.");
	windowSettings.width = windowData["size"][0];
	windowSettings.height = windowData["size"][1];

	if (!windowData.contains("background-color"))
		throw std::runtime_error("'background-color' is required.");
	windowSettings.backgroundColor = getColor(windowData["background-color"]);

	if (!windowData.contains("font-path"))
		throw std::runtime_error("'font-path' is required.");
	windowSettings.fontPath = windowData["font-path"];

	if (windowData.contains("font-size"))
		windowSettings.fontSize = windowData["font-size"];

	return windowSettings;
}

std::unordered_map<uint16_t, Key> LayoutParser::loadKeys() {
	if (!data.contains("keys"))
		throw std::runtime_error("'keys' is required.");		
	const json keysData = data["keys"];
	std::unordered_map<uint16_t, Key> keys;

	for (const auto keyData : keysData) {
		Key key;

		if (!keyData.contains("code"))
			throw std::runtime_error("'code' is required.");
		const uint16_t keyCode = keyData["code"];

		if (!keyData.contains("before"))
			throw std::runtime_error("'before' is required.");
		if (!keyData.contains("after"))
			throw std::runtime_error("'after' is required.");	
		const json keyBeforeData = keyData["before"];				
		const json keyAfterData = keyData["after"];

		if (!keyBeforeData.contains("rect"))
			throw std::runtime_error("'rect' is required.");	
		key.rect.before = getRect(keyBeforeData["rect"]);
		if (keyAfterData.contains("rect"))
			key.rect.after = getRect(keyAfterData["rect"]);
		else
			key.rect.after = key.rect.before;

		if (!keyBeforeData.contains("background-color"))
			throw std::runtime_error("'background-color' is required.");	
		key.backgroundColor.before = getColor(keyBeforeData["background-color"]);
		if (keyAfterData.contains("background-color"))
			key.backgroundColor.after = getColor(keyAfterData["background-color"]);
		else
			key.backgroundColor.after = key.backgroundColor.before;

		if (keyBeforeData.contains("label-content")) {
			key.labelContent.before = keyBeforeData["label-content"];
			if (keyAfterData.contains("label-content"))
				key.labelContent.after = keyAfterData["label-content"];
			else
				key.labelContent.after = key.labelContent.before;
		}

		if (!keyBeforeData.contains("label-color"))
			throw std::runtime_error("'label-color' is required.");	
		key.labelColor.before = getColor(keyBeforeData["label-color"]);
		if (keyAfterData.contains("label-color"))
			key.labelColor.after = getColor(keyAfterData["label-color"]);
		else
			key.labelColor.after = key.labelColor.before;		

		if (keys.find(keyCode) != keys.end())
			throw std::runtime_error("Key codes can't repeat.");
		keys[keyCode] = key;
	}

	return keys;
}