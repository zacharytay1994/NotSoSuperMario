#include "Sprite.h"

Sprite::Sprite(const std::string& path, const int& width, const int& height, const int& columns)
	:
	path_location_(path),
	width_(width),
	height_(height),
	columns_(columns)
{
}

Sprite::~Sprite()
{
}

bool Sprite::Initialize(Graphics& graphics)
{
	if (&graphics != nullptr) {
		texture_.initialize(&graphics, path_location_.c_str());
		image_.initialize(&graphics, width_, height_, columns_, &texture_);
		initialized_ = true;
		return true;
	}
	return false;
}

void Sprite::Update(const float& frametime)
{
	if (initialized_) {
		image_.update(frametime);
	}
}

void Sprite::Draw()
{
	if (initialized_) {
		image_.draw();
	}
}

void Sprite::InitializeAnimation(const int& startframe, const int& endframe, const float& animationdelay)
{
	image_.setFrames(startframe, endframe);
	image_.setFrameDelay(animationdelay);
	image_.setCurrentFrame(startframe);
}

Image& Sprite::GetImage()
{
	return image_;
}

int Sprite::GetWidth()
{
	return width_;
}

int Sprite::GetHeight()
{
	return height_;
}
