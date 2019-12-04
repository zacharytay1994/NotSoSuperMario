#pragma once

#include "GameObject.h"

class Input;
class ColliderManager;
class PhysicsComponent;
class Mario : public GameObject {
public:
	Sprite* normal_idle_;
	Sprite* normal_running_animation_;
	Sprite* normal_jumping_animation_;

	Sprite* super_idle_;
	Sprite* super_jumping_;
	Sprite* super_running_animation_;

	Sprite* idle_;
	Sprite* running_animation_;
	Sprite * jumping_;

	Sprite* dying_sprite;
	PhysicsComponent* phy_;
	bool looking_left = true;
	bool isDead = false;
	float turn_radius_ = 0.0f;
	float turn_rate_ = 250.0f;
	float deadVel = 0;
	float velocity = 250;
	bool deathAnimationDone = false;
	bool is_big_ = false;
public:
	Mario(Input& input, ColliderManager& cm);
	~Mario();
	void Update(const float& frametime) override;
	void Render() override;
	void ChildInitialize(Graphics& gfx) override;
	void ExecuteBounce();
};