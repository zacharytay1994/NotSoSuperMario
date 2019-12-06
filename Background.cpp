#include "Background.h"
#include "Vec2.h"

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
	if (force_update_) {
		sprite_.GetImage().setX(camera_.GetPosition().x_ * x_scroll_ + x_offset_ + x);
		sprite_.GetImage().setY(camera_.GetPosition().y_ * y_scroll_ + y_offset_ + y);
	}
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

void Background::LerpToPosition(const float& frametime)
{
	// get current position
	Vec2<float> current_pos = { sprite_.GetImage().getX() + sprite_.GetWidth()/2, sprite_.GetImage().getY() + sprite_.GetHeight()/2 };
	// get camera position
	Vec2<float> camera_pos = { camera_.GetPosition().x_ + x_offset_, camera_.GetPosition().y_ + y_offset_ };
	// get vector to camera
	Vec2<float> vec_to_cam = camera_pos - current_pos;
	// lerp to position if above threshold
	if (vec_to_cam.MagnitudeSq() > distance_threshold_ * distance_threshold_) {
		sprite_.GetImage().setX(sprite_.GetImage().getX() + vec_to_cam.x_ * lerp_strength_ * frametime);
		sprite_.GetImage().setY(sprite_.GetImage().getY() + vec_to_cam.y_ * lerp_strength_ * frametime);
	}
}

void Background::ForceUpdate(const bool& lerp)
{
	force_update_ = lerp;
}

void Background::SetLerpStrength(const float& strength)
{
	lerp_strength_ = strength;
}

void Background::SetPosition(const float& x, const float& y)
{
	sprite_.GetImage().setX(x);
	sprite_.GetImage().setY(y);
}

void Background::SetScrollRate(const float& scroll)
{
	scroll_rate_ = scroll;
}

void Background::ScrollBackground(const float& frametime)
{
	if (scroll_counter_ > scroll_range_ || scroll_counter_ < -scroll_range_) {
		scroll_rate_ *= -1;
	}
	scroll_counter_ += scroll_rate_ * frametime;
	x_offset_ += scroll_rate_ * frametime;
}
