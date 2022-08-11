#include "stdafx.h"

int main() {
	
	print("[+] ucrecoil by namespace#0722");

	std::thread recoil_thread(recoil::handle);
	std::thread keybind_thread(keys::handle);

	recoil_thread.detach();
	keybind_thread.detach();

	while (!GetAsyncKeyState(VK_END)) {
		SleepEx(1, false);
	}

	exit(0);

}