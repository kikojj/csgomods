#pragma once
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dwmapi.lib")

#include <map>
#include <string>
#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>
#include <stdexcept>
#include <Windows.h>
#include <functional>

#include "Render.hpp"

class c_overlay {
public:
	typedef std::function<void(c_overlay*, c_render*)> RenderFunction;

private:
	int width = 800;
	int height = 600;

	IDirect3D9Ex* d3d9 = nullptr;
	IDirect3DDevice9* d3d9_device = nullptr;
	ID3DXSprite* d3dx_sprite = nullptr;

	c_render* renderer = nullptr;

	std::vector<RenderFunction> render_stack;

public:
	HWND overlay;
	RECT desktop_rect;

	c_overlay(int&, int&, WNDPROC);

	int add_render(RenderFunction);

	void render();

	void loop();
};