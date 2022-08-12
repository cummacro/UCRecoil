#pragma once

#include "stdafx.h"

static LPDIRECT3D9              g_pD3D = NULL;
static LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;
static D3DPRESENT_PARAMETERS    g_d3dpp = {};

bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void ResetDevice();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

HWND hwnd;

static const char* weapons[] = { "assault rifle", "lr-300 rifle", "mp5a4", "thompson" };
static const char* scopes[] = { "iron sights", "simple sights" };

namespace menu {
	inline ImFont* MenuFont = 0;

	void keybinds() {
		items::current_gun = items::guns[globals::weaponid];
		items::current_scope = items::scopes[globals::scopeid];
	}

	void style()
	{
		ImGuiStyle* style = &ImGui::GetStyle();
		ImGuiIO& io = ImGui::GetIO();

		style->WindowBorderSize = 0;
		style->WindowRounding = 0;
		style->WindowTitleAlign = ImVec2(0.5, 0.5);
		style->WindowMinSize = ImVec2(600, 430);
		style->ButtonTextAlign = ImVec2(0.5, 0.5);

		style->Colors[ImGuiCol_TitleBg] = ImColor(255, 101, 53, 255);
		style->Colors[ImGuiCol_TitleBgActive] = ImColor(255, 101, 53, 255);
		style->Colors[ImGuiCol_TitleBgCollapsed] = ImColor(0, 0, 0, 130);

		style->Colors[ImGuiCol_Button] = ImColor(31, 30, 31, 255);
		style->Colors[ImGuiCol_ButtonActive] = ImColor(31, 30, 31, 255);
		style->Colors[ImGuiCol_ButtonHovered] = ImColor(41, 40, 41, 255);

		style->Colors[ImGuiCol_CheckMark] = ImColor(255, 101, 53, 255);

		style->Colors[ImGuiCol_SliderGrab] = ImColor(255, 101, 53, 255);
		style->Colors[ImGuiCol_SliderGrabActive] = ImColor(255, 80, 40, 255);

		style->Colors[ImGuiCol_Separator] = ImColor(70, 70, 70, 255);
		style->Colors[ImGuiCol_SeparatorActive] = ImColor(76, 76, 76, 255);
		style->Colors[ImGuiCol_SeparatorHovered] = ImColor(76, 76, 76, 255);

		style->Colors[ImGuiCol_FrameBg] = ImColor(37, 36, 37, 255);
		style->Colors[ImGuiCol_FrameBgActive] = ImColor(37, 36, 37, 255);
		style->Colors[ImGuiCol_FrameBgHovered] = ImColor(37, 36, 37, 255);

		style->Colors[ImGuiCol_Header] = ImColor(0, 0, 0, 0);
		style->Colors[ImGuiCol_HeaderActive] = ImColor(0, 0, 0, 0);
		style->Colors[ImGuiCol_HeaderHovered] = ImColor(46, 46, 46, 255);

		g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
		g_pd3dDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
		g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		g_pd3dDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
		g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		g_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

		g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
		g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, TRUE);
		g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		g_pd3dDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);

		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		g_pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		g_pd3dDevice->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, TRUE);
		g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		g_pd3dDevice->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_INVDESTALPHA);
		g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		g_pd3dDevice->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_ONE);

		g_pd3dDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, FALSE);
		g_pd3dDevice->SetRenderState(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN |
			D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_ALPHA);
	}

	void run() {
		WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 200L, 300L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, ((L"Main")), NULL };
		::RegisterClassEx(&wc);
		HWND hwnd = ::CreateWindow(wc.lpszClassName, ((L"Main")), WS_OVERLAPPEDWINDOW, 200, 300, 300, 400, NULL, NULL, wc.hInstance, NULL);
		::ShowWindow(::GetConsoleWindow(), SW_HIDE);
		if (!CreateDeviceD3D(hwnd))
		{
			CleanupDeviceD3D();
			::UnregisterClass(wc.lpszClassName, wc.hInstance);
			return;
		}
		::ShowWindow(hwnd, SW_SHOW);
		::UpdateWindow(hwnd);
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		MenuFont = io.Fonts->AddFontFromFileTTF("Minecraft.ttf", 16.000f);
		ImGui::StyleColorsDark();
		ImGui_ImplWin32_Init(hwnd);
		ImGui_ImplDX9_Init(g_pd3dDevice);

		MSG msg;

		while (1)
		{
			while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
			{
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
				if (msg.message == WM_QUIT)
					exit(0);
			}

			ImVec4* colors = ImGui::GetStyle().Colors;
			colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
			colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

			keybinds();

			ImGui_ImplDX9_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();
			{
				ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
				ImGui::SetNextWindowSize(ImVec2(284, 300), ImGuiCond_Always);

				ImGui::PushFont(MenuFont);

				ImGui::Begin(("Main"), (bool*)true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar);
				{
					ImGui::Text("recoil control");
					ImGui::Checkbox("##3", &globals::active);

					ImGui::Spacing();

					ImGui::Text("sensitivity");
					ImGui::SliderFloat("##1", &globals::sens, 0.f, 1.f);

					ImGui::Spacing();

					ImGui::Text("fov");
					ImGui::SliderFloat("##2", &globals::fov, 75.f, 90.f);

					ImGui::Spacing();

					ImGui::Combo("##4", &globals::weaponid, weapons, IM_ARRAYSIZE(weapons));
					ImGui::Combo("##5", &globals::scopeid, scopes, IM_ARRAYSIZE(scopes));

					ImGui::Spacing();

					ImGui::Separator();

					ImGui::Spacing(); ImGui::Spacing();

					ImGui::Text("namespace#0722");
				}
				ImGui::End();

				ImGui::PopFont();
			}
			ImGui::EndFrame();
			g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
			g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
			g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
			g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, NULL, 1.0f, 0);
			if (g_pd3dDevice->BeginScene() >= 0)
			{
				ImGui::Render();
				ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
				g_pd3dDevice->EndScene();
			}
			HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
			if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
				ResetDevice();
		}
		ImGui_ImplDX9_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
		CleanupDeviceD3D();
		::DestroyWindow(hwnd);
		::UnregisterClass(wc.lpszClassName, wc.hInstance);
		return;
	}
}

bool CreateDeviceD3D(HWND hWnd)
{
	if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
		return false;
	ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
	g_d3dpp.Windowed = TRUE;
	g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	g_d3dpp.EnableAutoDepthStencil = TRUE;
	g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
		return false;
	return true;
}
void CleanupDeviceD3D()
{
	if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
	if (g_pD3D) { g_pD3D->Release(); g_pD3D = NULL; }
}
void ResetDevice()
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
	if (hr == D3DERR_INVALIDCALL)
		IM_ASSERT(0);
	ImGui_ImplDX9_CreateDeviceObjects();
}
#ifndef WM_DPICHANGED
#define WM_DPICHANGED 0x02E0
#endif
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;
	switch (msg)
	{
	case WM_SIZE:
		if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
		{
			g_d3dpp.BackBufferWidth = LOWORD(lParam);
			g_d3dpp.BackBufferHeight = HIWORD(lParam);
			ResetDevice();
		}
		return 0;
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU)
			return 0;
		break;
	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0;
	case WM_DPICHANGED:
		break;
	}
	return ::DefWindowProc(hWnd, msg, wParam, lParam);
}