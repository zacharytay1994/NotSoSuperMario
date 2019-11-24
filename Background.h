#pragma once
#include "Vec2.h"
#include "Sprite.h"
#include "Camera.h"

#include <string>
#include <sstream>

class Graphics;
class Background {
private:
	Camera& camera_;
	float x_scroll_ = 0.4f;
	float y_scroll_ = 0.4f;
	float x_offset_ = -300.0f;
	float y_offset_ = -200.0f;

	int x_tile_ = 10;
	int y_tile_ = 1;

	Sprite sprite_;
	std::stringstream ss;
public:
	Background(const std::string& path, const int& width, const int& height, const int& cols, Camera& camera,
		const float& xscroll, const float& yscroll, const float& xoffset, const float& yoffset, const int& xtiling, const int& ytiling);
	~Background();
	void Update(const float& frametime);
	void Draw();
	void Initialize(Graphics& gfx);
	
	void UpdatePosition(const float& x, const float&y);
	void DrawTiles();
};