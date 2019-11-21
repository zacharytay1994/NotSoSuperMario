#include "Sprite.h"

Sprite::Sprite(const std::string& path, const int& width, const int& height, const int& cols)
	:
	path_location_(path),
	width_(width),
	height_(height),
	columns_(cols)
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

void Sprite::SetX(const float& x)
{
	if (initialized_) {
		image_.setX(x);
	}
}

int Sprite::GetX()
{
	if (initialized_) {
		return image_.getX();
	}
}

void Sprite::SetY(const float& y)
{
	if (initialized_) {
		image_.setY(y);
	}
}

int Sprite::GetY()
{
	return 0;
}
