#include "Background.h"

Background::Background(const std::string& path, const int& width, const int& height, const int& cols, Camera& camera,
	const float& xscroll, const float& yscroll, const float& xoffset, const float& yoffset, const int& xtiling, const int& ytiling)
	:
	sprite_(path, width, height, cols),
	camera_(camera),
	x_scroll_(xscroll),
	y_scroll_(yscroll),
	x_offset_(xoffset),
	y_offset_(yoffset),
	x_tile_(xtiling),
	y_tile_(ytiling)
{
}

Background::~Background()
{
}

void Background::Update(const float& frametime)
{
	sprite_.Update(frametime);
}

void Background::Draw()
{
	DrawTiles();
}

void Background::Initialize(Graphics& gfx)
{
	sprite_.Initialize(gfx);
	sprite_.GetImage().setX(100.0f);
	sprite_.GetImage().setY(100.0f);
	sprite_.GetImage().setScale(CAMERA_ZOOM);
}

void Background::UpdatePosition(const float& x, const float& y)
{
	sprite_.GetImage().setX(camera_.GetPosition().x_ * x_scroll_ + x_offset_ + x);
	sprite_.GetImage().setY(camera_.GetPosition().y_ * y_scroll_ + y_offset_ + y);
}

void Background::DrawTiles()
{
	for (int y = 0; y < y_tile_; y++) {
		for (int x = 0; x < x_tile_; x++) {
			UpdatePosition(sprite_.GetWidth() * x, sprite_.GetHeight() * y);
			sprite_.Draw();
		}
	}
}
