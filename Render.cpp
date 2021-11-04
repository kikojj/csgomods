#include "Render.hpp"

c_render::c_render(IDirect3DDevice9* device) {
	if (device == nullptr) {
		throw std::runtime_error("IDirect3DDevice9 pointer is nullptr");
	}

	this->d3d9_device = device;

	if (FAILED(D3DXCreateFontW(this->d3d9_device, 8, 0, FW_NORMAL, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, (LPCWSTR)"Roboto", &this->d3dx_fonts[en_font_type::ROBOTO_8].first))) {
		throw std::runtime_error("Failed: create d3d9 font(Roboto 8)");
	}

	if (FAILED(D3DXCreateFontW(this->d3d9_device, 10, 0, FW_NORMAL, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, (LPCWSTR)"Roboto", &this->d3dx_fonts[en_font_type::ROBOTO_10].first))) {
		throw std::runtime_error("Failed: create d3d9 font(Roboto 10)");
	}

	if (FAILED(D3DXCreateFontW(this->d3d9_device, 12, 0, FW_NORMAL, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, (LPCWSTR)"Roboto", &this->d3dx_fonts[en_font_type::ROBOTO_12].first))) {
		throw std::runtime_error("Failed: create d3d9 font(Roboto 12)");
	}

	if (FAILED(D3DXCreateFontW(this->d3d9_device, 14, 0, FW_NORMAL, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, (LPCWSTR)"Roboto", &this->d3dx_fonts[en_font_type::ROBOTO_14].first))) {
		throw std::runtime_error("Failed: create d3d9 font(Roboto 14)");
	}
}

void c_render::line(D3DXVECTOR2 points[], int points_size, DWORD color, float line_width, bool antialias) {
	ID3DXLine* d3dx_line;
	D3DXCreateLine(this->d3d9_device, &d3dx_line);

	d3dx_line->SetWidth(line_width);
	d3dx_line->SetGLLines(true);

	if (antialias) {
		d3dx_line->SetAntialias(antialias);
	}

	d3dx_line->Begin();
	d3dx_line->Draw(points, points_size, color);
	d3dx_line->End();
	d3dx_line->Release();
}

void c_render::_rect(float x, float y, float w, float h, DWORD color) {
	D3DXVECTOR2 points[] = { D3DXVECTOR2(x, y + h / 2), D3DXVECTOR2(x + w, y + h / 2) };
	line(points, 2, color, h);
}

void c_render::rect(s_rect_styles styles) {
	if (styles.width == 0 || styles.height == 0) {
		return;
	}

	if (styles.fill) {
		this->_rect(styles.x, styles.y, styles.width, styles.height, styles.fill_color);
	}

	if (styles.border && styles.border_width != 0) {
		this->_rect(styles.x, styles.y, styles.width, styles.border_width, styles.border_color);
		this->_rect(styles.x + styles.width - styles.border_width, styles.y, styles.border_width, styles.height, styles.border_color);
		this->_rect(styles.x, styles.y + styles.height - styles.border_width, styles.width, styles.border_width, styles.border_color);
		this->_rect(styles.x, styles.y, styles.border_width, styles.height, styles.border_color);
	}
}

void c_render::text(const std::string& str, s_text_styles styles) {
	if (str == "") {
		return;
	}

	auto d3dx_font = this->d3dx_fonts[styles.font_type].first;
	auto d3dx_font_size = this->d3dx_fonts[styles.font_type].second;

	if (styles.width < 0) {
		styles.width = 120;
	}

	if (styles.height < 0) {
		styles.height = d3dx_font_size;
	}

	if (styles.outline) {
		RECT rect_font_top_right_offset = { styles.x + 1, styles.y + 1, styles.x + styles.width, styles.height };
		d3dx_font->DrawTextW(nullptr, to_wstring(str).c_str(), str.size(), &rect_font_top_right_offset, DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));
		RECT rect_font_bottom_left_offset = { styles.x - 1, styles.y - 1, styles.x + styles.width, styles.height };
		d3dx_font->DrawTextW(nullptr, to_wstring(str).c_str(), str.size(), &rect_font_bottom_left_offset, DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));
		RECT rect_font_bottom_right_offset = { styles.x + 1, styles.y - 1, styles.x + styles.width, styles.height };
		d3dx_font->DrawTextW(nullptr, to_wstring(str).c_str(), str.size(), &rect_font_bottom_right_offset, DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));
		RECT rect_font_top_left_offset = { styles.x - 1, styles.y + 1, styles.x + styles.width, styles.height };
		d3dx_font->DrawTextW(nullptr, to_wstring(str).c_str(), str.size(), &rect_font_top_left_offset, DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));
	}

	RECT rect_font = { styles.x, styles.y, styles.x + styles.width, styles.height };
	d3dx_font->DrawTextW(nullptr, to_wstring(str).c_str(), str.size(), &rect_font, DT_NOCLIP, styles.color);
}

int c_render::get_text_width(const std::string& str, en_font_type font_type) {
	auto d3dx_font = this->d3dx_fonts[font_type].first;

	RECT rect = { 0, 0, 0, 0 };

	d3dx_font->DrawTextA(nullptr, str.c_str(), -1, &rect, DT_CALCRECT, D3DCOLOR_ARGB(0, 0, 0, 0));

	return rect.right - rect.left;
}

int c_render::get_text_height(const std::string& str, en_font_type font_type) {
	auto d3dx_font = this->d3dx_fonts[font_type].first;

	RECT rect = { 0, 0, 0, 0 };

	d3dx_font->DrawTextA(nullptr, str.c_str(), -1, &rect, DT_CALCRECT, D3DCOLOR_ARGB(0, 0, 0, 0));

	return rect.bottom - rect.top;
}

std::wstring c_render::to_wstring(const std::string& str) {
	return std::wstring(str.begin(), str.end());
}