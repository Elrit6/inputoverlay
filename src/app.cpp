#include "app.hpp"

#include <iostream>
#include "key.hpp"

void App::quit() {
	keyListener.uninstallHook();
	window.exitSDL();
	std::exit(0);
}

void App::loop() {
	while (true) {
		if (!window.handleEvents())
			quit();
		window.drawKeys(keys, pressedKeys);
	}
}

App::App() {
	layoutParser.parse();
	keys = layoutParser.loadKeys();
	window.initSDL(layoutParser.loadWindowSettings());

	keyListener.setCallback([this](const int32_t keyEventCode, const bool keyEventState) {
		if (keyEventState)
			pressedKeys.insert(keyEventCode);
		else
			pressedKeys.erase(keyEventCode);
	});
	keyListener.installHook();
	keyListener.startListening();

	loop();
}