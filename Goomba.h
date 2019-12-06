#pragma once
#include "GameObject.h"
#include "Vec2.h"

class Input;
class ColliderManager;
class PhysicsComponent;
class Goomba : public GameObject {
private:
	Sprite* walking_sprite_;
	Sprite* death_sprite_;
	Sprite* idle_sprite_;
	bool looking_left_ = false;
	PhysicsComponent* phy_;
	Vec2<float> direction_ = { -1.0f, 0.0f };
	float speed_ = 10.0f;
public:
	Goomba(ColliderManager& cm, const Vec2<float>& position);
	~Goomba();
	void Update(const float& frametime) override;
	void Render() override;
	void ChildInitialize(Graphics& gfx) override;
};