#pragma once

#include <map>
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <iostream>
#include <stdexcept>

class c_render {
private:
	IDirect3DDevice9* d3d9_device = nullptr;

public:
	enum class en_font_type: int {
		ROBOTO_8,
		ROBOTO_10,
		ROBOTO_12,
		ROBOTO_14,
	};
private:
	std::map<en_font_type, std::pair<ID3DXFont*, float>> d3dx_fonts;

public:
	c_render(IDirect3DDevice9*);

private:
	struct s_base_styles {
		float x = 0;
		float y = 0;
	};

	std::wstring to_wstring(const std::string&);

	void _rect(float x, float y, float w, float h, DWORD color);

public:

	void line(D3DXVECTOR2[], int, DWORD, float = 1.f, bool = false);

	struct s_rect_styles : s_base_styles {
		float width = 0;
		float height = 0;
		bool fill = false;
		DWORD fill_color = 0x00000000;
		bool border = false;
		DWORD border_color = 0x00000000;
		float border_width = 0;
	};
	void rect(s_rect_styles);

	struct s_text_styles : s_base_styles {
		DWORD color = 0x00000000;
		bool outline = false;
		en_font_type font_type = en_font_type::ROBOTO_14;
		float width = -1;
		float height = -1;
	};
	void text(const std::string&, s_text_styles);

	int get_text_width(const std::string&, en_font_type = en_font_type::ROBOTO_14);

	int get_text_height(const std::string&, en_font_type = en_font_type::ROBOTO_14);
};