#pragma once

#include "stdafx.h"

// shout out to randy shanks my boy

namespace util {
	inline void sleep(int64_t sleep_ms, std::chrono::time_point<std::chrono::steady_clock> start)
	{
		sleep_ms *= 1000;

		auto truncated = (sleep_ms - std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count()) / 1000;

		while (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count() < sleep_ms)
		{
			if (truncated)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(truncated));
				truncated = 0;
			}
		}
	}

	inline bool move(vec2 pos)
	{
		INPUT input;
		input.type = INPUT_MOUSE;
		input.mi.mouseData = 0;
		input.mi.time = 0;
		input.mi.dx = static_cast<int>(pos.x);
		input.mi.dy = static_cast<int>(pos.y);
		input.mi.dwFlags = MOUSEEVENTF_MOVE;
		return SendInput(1, &input, sizeof(input));
	}

	inline void lerp(vec2 pos, double animation, double repeat_delay, std::chrono::time_point<std::chrono::steady_clock> f_excess)
	{
		std::chrono::time_point<std::chrono::steady_clock> excess = f_excess;
		int previous_x = 0, previous_y = 0; double previous_a = 0.0;
		for (int index = 1; index < static_cast<int>(animation); index++)
		{
			int x = index * static_cast<int>(pos.x) / static_cast<int>(animation);
			int y = index * static_cast<int>(pos.y) / static_cast<int>(animation);

			int a = index * 1.0;

			move(vec2{ (float)x - (float)previous_x, (float)y - (float)previous_y });

			sleep(a - previous_a, excess);

			excess = std::chrono::high_resolution_clock::now();

			previous_x = x; previous_y = y; previous_a = a;
		}

		if (repeat_delay - animation > 0) sleep(repeat_delay - animation, excess);
	}

	inline vec2 get_pixels(vec2 angles) {
		return angles / (-0.03 * globals::sens * 3.0 * (globals::fov / 100.0));
	}

	inline float get_animation(vec2 angles) {
		return (sqrt(pow(angles.x, 2) + pow(angles.y, 2))) / 20.f * 1000.f;
	}
}