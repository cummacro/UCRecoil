#include "stdafx.h"

int main() {

	std::thread recoil_thread(recoil::handle);
	std::thread keybind_thread(keys::handle);
	std::thread menu_thread(menu::run);

	recoil_thread.detach();
	keybind_thread.detach();
	menu_thread.detach();

	while (!GetAsyncKeyState(VK_END)) {
		SleepEx(1, false);
	}

	exit(0);

}