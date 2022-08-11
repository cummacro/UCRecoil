#include "stdafx.h"

int main() {
	int current_shot;

	// creds to excess time idea to randy shanks pretty cool idea
	auto excess_time = std::chrono::high_resolution_clock::now();

	while (1) {
		while (!(GetAsyncKeyState(VK_LBUTTON) && GetAsyncKeyState(VK_RBUTTON))) {
			SleepEx(1, false);
			excess_time = std::chrono::high_resolution_clock::now();
			keys::handle();
		}

		for (current_shot = 0; current_shot < items::current_gun->pattern.size(); current_shot++) {
			if (!GetAsyncKeyState(VK_LBUTTON))
				break;

			vec2 angles = items::current_gun->pattern[current_shot];

			vec2 pos = util::get_pixels(angles);
			float animation_time = util::get_animation(angles);

			util::lerp(pos, animation_time, items::current_gun->rate, excess_time);

			excess_time = std::chrono::high_resolution_clock::now();
		}

		while (GetAsyncKeyState(VK_LBUTTON)) {
			SleepEx(1, false);
			excess_time = std::chrono::high_resolution_clock::now();
		}
	}
}