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

// Get functions
Image& Sprite::GetImage()
{
	return image_;
}

int Sprite::GetWidth()
{
	return width_ * CAMERA_ZOOM;
}

int Sprite::GetHeight()
{
	return height_ * CAMERA_ZOOM;
}

// Set functions
void Sprite::SetX(int x)
{
	image_.setX(x);
}

void Sprite::SetY(int y)
{
	image_.setY(y);
}

void Sprite::SetCurrentFrame(int c)
{
	image_.setCurrentFrame(c);
	image_.setRect();
}