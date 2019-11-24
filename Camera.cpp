#include "Camera.h"
#include "GameObject.h"

Camera::Camera()
	:
	center_screen_({GAME_WIDTH/2, GAME_HEIGHT/2})
{
}

Camera::~Camera()
{
}

void Camera::SyncTargetPosition()
{
	if (target_ != nullptr) {
		// clamps camera
		float y = min(target_->GetPosition().y, max_y_);
		y = max(y, min_y_);
		float x = min(target_->GetPosition().x, max_x_);
		x = max(x, min_x_);
		position_ = { x, y };
	}
}

void Camera::UpdateCameraTransform()
{
	camera_transform_.x_ = position_.x_ > center_screen_.x_ ? -(position_.x_ - center_screen_.x_) : center_screen_.x_ - position_.x_;
	camera_transform_.y_ = position_.y_ > center_screen_.y_ ? -(position_.y_ - center_screen_.y_) : center_screen_.y_ - position_.y_;
}

Vec2<float> Camera::GetCameraTransform()
{
	return camera_transform_;
}

void Camera::SetTarget(GameObject* go)
{
	target_ = go;
}

void Camera::Update(const float& frametime)
{
	SyncTargetPosition();
	UpdateCameraTransform();
}

Vec2<float> Camera::GetPosition()
{
	return position_;
}
