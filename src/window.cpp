#include "window.hpp"

#include <stdexcept>

template <typename Type>
Type Window::getProperty(const Property<Type>& value, const bool isAfter) {
	return isAfter ? value.after : value.before;
}

SDL_Rect Window::toSDLRect(const Rect& rect) {
	return SDL_Rect {
		rect.x,
		rect.y,
		rect.w,
		rect.h
	};
};

void Window::clear() {
	SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, 255);
	SDL_RenderClear(renderer);
}

void Window::drawRect(const Rect& rect, const Color& color) {
	SDL_Rect sdlRect = toSDLRect(rect);

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);	
	SDL_RenderFillRect(renderer, &sdlRect);		
}

void Window::drawCenteredText(const Rect& rect, const Rect& keyRect, const Color& color, const std::string& text) {
	SDL_Color sdlColor = {color.r, color.g, color.b, 255};
	SDL_Surface *textSurface = TTF_RenderText_Solid(font, text.c_str(), sdlColor);
	if (!textSurface)
		throw std::runtime_error(TTF_GetError());
	SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	if (!textTexture)
    	throw std::runtime_error(SDL_GetError());

	SDL_Rect sdlRect = {
		keyRect.x + (keyRect.w - textSurface->w) / 2,
		keyRect.y + (keyRect.h - textSurface->h) / 2,
		textSurface->w,
		textSurface->h
	};
	SDL_RenderCopy(renderer, textTexture, NULL, &sdlRect);
}

void Window::render() {
	SDL_RenderPresent(renderer);
}

void Window::initSDL(const WindowSettings& windowSettings) {
	const char* title = "input overlay";
	backgroundColor = windowSettings.backgroundColor;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw std::runtime_error(SDL_GetError());
	if (TTF_Init() < 0)
		throw std::runtime_error(TTF_GetError());

	window = SDL_CreateWindow(
		title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		windowSettings.width, windowSettings.height, SDL_WINDOW_RESIZABLE
	);
	if (!window)
		throw std::runtime_error(SDL_GetError());
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
		throw std::runtime_error(SDL_GetError());
	font = TTF_OpenFont(windowSettings.fontPath.c_str(), windowSettings.fontSize);
	if (!font)
		throw std::runtime_error("Couldn't load the font.");	
}

void Window::exitSDL() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_CloseFont(font);
	SDL_Quit();
}

bool Window::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				return false;
		}
	}
	return true;
}

void Window::drawKeys(const std::unordered_map<uint16_t, Key>& keys, const std::unordered_set<uint16_t>& pressed) {
	clear();
	for (const auto& [keyCode, key] : keys) {
		const bool isAfter = pressed.find(keyCode) != pressed.end();

		const Rect keyRect = getProperty<Rect>(key.rect, isAfter);
		const Color keyColor = getProperty<Color>(key.backgroundColor, isAfter);
		const std::string keyLabelContent = getProperty<std::string>(key.labelContent, isAfter);
		const Color keyLabelColor = getProperty<Color>(key.labelColor, isAfter);

		drawRect(keyRect, keyColor);

		drawCenteredText(
			Rect {keyRect.x, keyRect.y, 0, 0},
			keyRect,
			keyLabelColor,
			keyLabelContent
		);
	}
	render();
}