#pragma once

#include "GameObject.h"

class Input;
class ColliderManager;
class PhysicsComponent;
class Mario : public GameObject {
public:
	Sprite* running_animation_;
	Sprite* jumping_animation_;
	PhysicsComponent* phy_;
	bool looking_left = true;
	int animation_id_ = 0; // 0 = idle, 1 = running, 2 = jumping
public:
	Mario(Input& input, ColliderManager& cm);
	~Mario();
	void Update(const float& frametime) override;
	void Render() override;
	void ChildInitialize(Graphics& gfx) override;
	void ExecuteBounce();
};