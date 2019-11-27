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
	Sprite(const std::string& path, const int& width, const int& height, const int& columns);
	~Sprite();
	bool Initialize(Graphics& graphics);
	void Update(const float& frametime);
	void Draw();

	void InitializeAnimation(const int& startframe, const int& endframe, const float& animationdelay);

	// Get functions
	Image& GetImage();
	int GetWidth();
	int GetHeight();

	// Set functions
	void SetX(int x);
	void SetY(int y);
	void SetCurrentFrame(int c);
};