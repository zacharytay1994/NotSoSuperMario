#pragma once
#include "GameObject.h"
#include "Vec2.h"
#include <cstdlib>

class Input;
class ColliderManager;
class PhysicsComponent;

class KoopaTroopa : public GameObject {
private:
	int random;    //range 1 to 10
	float timer;
	bool shellState = false;
	Sprite* walking_sprite_;
	Sprite* shellmoving_sprite_;
	Sprite* shellidle_sprite_;
	bool looking_left_ = false;
	PhysicsComponent* phy_;
	Vec2<float> direction_ = { -1.0f, 0.0f };
	float speed_ = 25.0f;
	float shellSpeed_ = 150.0f;
	bool shellMoving = false;

public:
	KoopaTroopa(ColliderManager& cm, const Vec2<float>& position);
	~KoopaTroopa();
	void Update(const float& frametime) override;
	void Render() override;
	void ChildInitialize(Graphics& gfx) override;
	bool GetShellState();
	bool GetShellMovingState();
};