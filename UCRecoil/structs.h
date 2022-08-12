#pragma once

#include "stdafx.h"

struct vec2 {
	float x, y;

	inline vec2(float x, float y) { this->x = x; this->y = y; };

	inline vec2 operator/(float a) {
		return vec2(this->x / a, this->y / a);
	}

	inline vec2 operator*(float a) {
		return vec2(this->x * a, this->y * a);
	}
};

struct gun {
	std::string name;
	std::vector<vec2> pattern;
	float rate;
};

struct scope {
	std::string name;
	float multiplier;
};