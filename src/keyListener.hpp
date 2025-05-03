#pragma once

#include <atomic>
#include <cstdint>
#include <functional>
#include <windows.h>

class KeyListener {
private:
	static std::atomic<bool> keyEventFlag;
	static std::atomic<bool> keyState;
	static std::atomic<int32_t> keyCode;
	std::function<void(const int32_t keyEventCode, const bool keyEventState)> callback;
	HHOOK hook;
	void handleKeyEvents();
	static LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);	

public:
	KeyListener();
	void setCallback(const std::function<void(const int32_t keyEventCode, const bool keyEventState)>& newCallback);
	void installHook();
	void startListening();
	void uninstallHook();
};