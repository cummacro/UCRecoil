#pragma once

#include "stdafx.h"

namespace keys {

	std::map<gun_ids, int> gun_keys {
		{ gun_ids::ak, VK_F3 },
		{ gun_ids::lr, VK_F4 },
		{ gun_ids::mp5, VK_F5 },
		{ gun_ids::thomp, VK_F6 },
	};

	std::map<scope_ids, int> scope_keys {
		{ scope_ids::none, VK_F7 },
		{ scope_ids::simple, VK_F8 }
	};

	inline void handle() {
		while (1) {

			for (auto keys : gun_keys) {
				if (GetAsyncKeyState(keys.second)) {
					globals::weaponid = keys.first;
					//items::current_gun = items::guns[keys.first];
				}
			}

			for (auto keys : scope_keys) {
				if (GetAsyncKeyState(keys.second)) {
					globals::scopeid = keys.first;
					//items::current_scope = items::scopes[keys.first];
				}
			}

			SleepEx(1, false);

		}
	}
}