#pragma once

#include <cstdint>
#include <unordered_map>
#include <unordered_set>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "windowSettings.hpp"
#include "graphicsTypes.hpp"
#include "key.hpp"

class Window {
private:
	Color backgroundColor;
	TTF_Font* font;
	SDL_Window* window;
	SDL_Renderer* renderer;
	template <typename Type>
	Type getProperty(const Property<Type>& value, const bool isAfter);
	SDL_Rect toSDLRect(const Rect& rect);
	void clear();
	void drawRect(const Rect& rect, const Color& color);
	void drawCenteredText(const Rect& rect, const Rect& toCenterRect, const Color& color, const std::string& text);
	void render();

public:
	void initSDL(const WindowSettings& windowSettings);
	void exitSDL();
	bool handleEvents();
	void drawKeys(const std::unordered_map<uint16_t, Key>& keys, const std::unordered_set<uint16_t>& pressed);
};