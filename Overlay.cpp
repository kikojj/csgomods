#include "Overlay.hpp"

c_overlay::c_overlay(int& screen_width, int& screen_height, WNDPROC windows_procedure) {
	const HWND desktop = GetDesktopWindow();

	if (desktop != nullptr){
		GetWindowRect(desktop, &this->desktop_rect);

		screen_width = this->desktop_rect.right - this->desktop_rect.left;
		screen_height = this->desktop_rect.bottom - this->desktop_rect.top;

		this->width = screen_width;
		this->height = screen_height;
	}
	else {
		throw std::runtime_error("Invalid desktop window");
	}

	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = windows_procedure;
	wc.hInstance = nullptr;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = HBRUSH(RGB(0, 0, 0));
	wc.lpszClassName = (LPCWSTR)" ";
	RegisterClassEx(&wc);

	this->overlay = CreateWindowExW(0, (LPCWSTR)" ", (LPCWSTR)" ", WS_EX_TOPMOST | WS_POPUP, this->desktop_rect.left, this->desktop_rect.top, this->width, this->height, nullptr, nullptr, nullptr, nullptr);
	SetWindowLongW(this->overlay, GWL_EXSTYLE, GetWindowLong(this->overlay, GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW);
	SetLayeredWindowAttributes(this->overlay, RGB(0, 0, 0), 0, ULW_COLORKEY);
	SetLayeredWindowAttributes(this->overlay, 0, 255, LWA_ALPHA);
	ShowWindow(this->overlay, SW_SHOWDEFAULT);

	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &this->d3d9))) {
		throw std::runtime_error("Failed: create d3d9");
	}

	D3DPRESENT_PARAMETERS d3dp_params;
	ZeroMemory(&d3dp_params, sizeof(D3DPRESENT_PARAMETERS));
	d3dp_params.Windowed = 1;
	d3dp_params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dp_params.hDeviceWindow = this->overlay;
	d3dp_params.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dp_params.BackBufferWidth = this->width;
	d3dp_params.BackBufferHeight = this->height;
	d3dp_params.EnableAutoDepthStencil = 1;
	d3dp_params.AutoDepthStencilFormat = D3DFMT_D16;


	if (FAILED(this->d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, this->overlay, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dp_params, &this->d3d9_device))) {
		throw std::runtime_error("Failed: create d3d9 device");
	}

	this->renderer = new c_render(this->d3d9_device);

	if (FAILED(D3DXCreateSprite(this->d3d9_device, &this->d3dx_sprite))) {
		throw std::runtime_error("Failed: create d3dx sprite");
	}
}

int c_overlay::add_render(RenderFunction function) {
	this->render_stack.push_back(function);
	return this->render_stack.size() - 1;
}

void c_overlay::render() {
	this->d3d9_device->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1, 0);
	this->d3d9_device->BeginScene();

	for (auto render_func: this->render_stack) {
		render_func(this, this->renderer);
	}

	this->d3d9_device->EndScene();
	this->d3d9_device->Present(nullptr, nullptr, nullptr, nullptr);
}

void c_overlay::loop() {
	MSG msg;

	SetWindowPos(this->overlay, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	this->render();

	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}