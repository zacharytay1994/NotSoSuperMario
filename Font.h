#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "graphics.h"
#include "Sprite.h"
#include "Vec2.h"
#include "Camera.h"

class Font
{
public:
	//Font(const std::string& filename, Graphics& gfx, Camera& camera, DWORD chroma = D3DCOLOR_XRGB(255, 0, 255));
	Font(const std::string& filename, Graphics& gfx, Camera& camera, float fontscale=1, DWORD chroma = D3DCOLOR_XRGB(255, 0, 255));
	void DrawTextString(const std::string& text, const Vec2<int>& pos, Graphics& gfx) const;
private:
	Sprite* font_sprite_;
	Camera* camera_;
	float fontscale_;

	// this gives the dimensions of a glyph in the font sheet
	static constexpr int glyph_width_ = 16;
	static constexpr int glyph_height_ = 28;
	// number of rows / columns in the font sheet (this is fixed)
	static constexpr int nColumns = 32;
	static constexpr int nRows = 3;
	// font sheet chroma color
	DWORD chroma = D3DCOLOR_XRGB(255, 0, 255);
	// start and end drawable character codes
	static constexpr char first_char_ = ' ';
	static constexpr char last_char_ = '~';
};