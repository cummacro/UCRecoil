#pragma once

#include <Windows.h>
#include <iostream>
#include <vector>
#include <thread>
#include <map>

#include <d3d9.h>
#include <d3dx9.h>
#include <Uxtheme.h>
#include <dwmapi.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dwmapi.lib")

#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"

#include "globals.h"
#include "structs.h"
#include "util.h"
#include "items.h"
#include "keys.h"
#include "recoil.h"
#include "menu.h"

#define print(x) std::cout << x << std::endl