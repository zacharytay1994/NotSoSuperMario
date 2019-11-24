#pragma once
#include "Vec2.h"
#include "constants.h"

class GameObject;
class Camera {
private:
	GameObject* target_;
	Vec2<float> center_screen_ = { GAME_WIDTH / 2, GAME_HEIGHT / 2 };
	Vec2<float> position_ = { 0.0f, 0.0f };
	Vec2<float> camera_transform_ = { 0.0f, 0.0f };
	float min_y_ = -500.0f;
	float max_y_ = 200.0f;
	float min_x_ = 100.0f;
	float max_x_ = 3200.0f;
public:
	Camera();
	~Camera();
	void SyncTargetPosition();
	void UpdateCameraTransform();
	Vec2<float> GetCameraTransform();
	void SetTarget(GameObject* go);

	void Update(const float& frametime);
	Vec2<float> GetPosition();
};