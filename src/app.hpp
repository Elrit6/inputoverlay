#pragma once

#include <unordered_map>
#include <unordered_set>
#include "layoutParser.hpp"
#include "window.hpp"
#include "keyListener.hpp"

class App {
private:
	std::unordered_set<uint16_t> pressedKeys = {};
	std::unordered_map<uint16_t, Key> keys;
	LayoutParser layoutParser;
	Window window;
	KeyListener keyListener;
	void quit();
	void loop();

public:
	App();
};

// TODO: handle key pressed without locking up the hook thread