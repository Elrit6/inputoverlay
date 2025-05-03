#include "keyListener.hpp"

#include <iostream> //
#include <stdexcept>
#include <thread>

static KeyListener* instance = nullptr;

std::atomic<bool> KeyListener::keyEventFlag(false);
std::atomic<bool> KeyListener::keyState;
std::atomic<int32_t> KeyListener::keyCode;

void KeyListener::handleKeyEvents() {
	while (true) {
		if (!keyEventFlag.load())
			continue;
		keyEventFlag.store(false);
		callback(keyCode.load(), keyState.load());
	}
}

LRESULT CALLBACK KeyListener::KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode == HC_ACTION) {
		PKBDLLHOOKSTRUCT keyEvent = (PKBDLLHOOKSTRUCT)lParam;

		keyCode.store(keyEvent->vkCode);
		switch (wParam) {
			case WM_KEYDOWN:
			case WM_SYSKEYDOWN:
				keyState.store(true);
				break;
			case WM_KEYUP:
			case WM_SYSKEYUP:
				keyState.store(false);
				break;
        }
        keyEventFlag.store(true);
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

KeyListener::KeyListener() {
	instance = this;
};

void KeyListener::setCallback(const std::function<void(const int32_t keyEventCode, const bool keyEventState)>& newCallback) {
	callback = newCallback;
}

void KeyListener::installHook() {
	hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
	if (hook == NULL)
		throw std::runtime_error("Installing the Windows hook failed.");
}

void KeyListener::startListening() {
	std::thread([this]{
		this->handleKeyEvents();
	}).detach();
	std::thread([this]{
		MSG msg;
		while (GetMessage(&msg, NULL, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}).detach();
}

void KeyListener::uninstallHook() {
	UnhookWindowsHookEx(hook);
}