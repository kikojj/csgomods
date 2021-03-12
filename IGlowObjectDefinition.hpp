#pragma once
#include <cstdint>

#include "ColorRGBA.hpp"

enum GlowStyle {
	GLOW_STYLE_FULL_BODY,
	GLOW_STYLE_INLINE_FLICKER,
	GLOW_STYLE_INLINE,
	GLOW_STYLE_FLICKER,
};

struct IGlowObjectDefinition {
public:
	uintptr_t		dwBaseEntity;								//0x0000
	float				glowColor[4];								//0x0004
private:
	DWORD				somehandle;									//0x0014 
	float				somefloat;									//0x0018 
public:
	float				bloomAmount;								//0x001C
	float				noise;											//0x0020
	bool				renderWhenOccluded;					//0x0024
	bool				renderWhenUnoccluded;				//0x0025
	bool				fullBloomRender;						//0x0026
private:
	BYTE				pad_0x0027[0x1];						//0x0027
public:
	int					fullBloomStencilTestValue;	//0x0028
	int					glowStyle;									//0x002C
	int					splitScreenSlot;						//0x0030
	int					nextFreeSlot;								//0x0034

public:
	/// <summary>
	/// set color params
	/// </summary>
	/// <param name="r">[0, 255]</param>
	/// <param name="g">[0, 255]</param>
	/// <param name="b">[0, 255]</param>
	/// <param name="a">[0, 255]</param>
	void color(float r, float g, float b, float a) {
		glowColor[0] = r / 255.f;
		glowColor[1] = g / 255.f;
		glowColor[2] = b / 255.f;
		glowColor[3] = a / 255.f;
	}

	/// <summary>
	/// set color
	/// </summary>
	/// <param name="color">(r[0, 255], g[0, 255], b[0, 255], a[0, 255])</param>
	void color(colorRGBA color) {
		glowColor[0] = color.r / 255.f;
		glowColor[1] = color.g / 255.f;
		glowColor[2] = color.b / 255.f;
		glowColor[3] = color.a / 255.f;
	}
};