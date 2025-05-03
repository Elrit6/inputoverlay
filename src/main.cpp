#include <iostream>
#include <stdexcept>
#include "app.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	try {
		App app;
	} catch (const std::exception& error) {
		std::cerr << error.what() << std::endl;
		return 1;
	}
	return 0;
}