#pragma once

#include "textureManager.h"
#include "image.h"
#include <string>
#include <cstring>

class Sprite {
private:
	TextureManager texture_;
	Image image_;
	std::string path_location_;
	int width_;
	int height_;
	int columns_;
	bool initialized_ = false;
public:
	Sprite(const std::string& path, const int& width, const int& height, const int& cols);
	~Sprite();
	bool Initialize(Graphics& graphics);
	void Update(const float& frametime);
	void Draw();

	// other functions
	void SetX(const float& x);
	int GetX();
	void SetY(const float& y);
	int GetY();
};