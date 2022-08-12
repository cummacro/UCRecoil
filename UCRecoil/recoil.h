#pragma once

#include "stdafx.h"

namespace recoil {
	inline void handle() {
		int current_shot;

		// creds to excess time idea to randy shanks pretty cool idea
		auto excess_time = std::chrono::high_resolution_clock::now();

		while (1) {
			while (!(GetAsyncKeyState(VK_LBUTTON) && GetAsyncKeyState(VK_RBUTTON)) || !globals::active) {
				SleepEx(1, false);
				excess_time = std::chrono::high_resolution_clock::now();
			}

			for (current_shot = 0; current_shot < items::current_gun->pattern.size(); current_shot++) {
				if (!GetAsyncKeyState(VK_LBUTTON))
					break;

				vec2 angles = items::current_gun->pattern[current_shot] / 2.f;

				if (GetAsyncKeyState(VK_LCONTROL))
					angles = angles / 2.f;

				angles = angles * items::current_scope->multiplier;

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
}