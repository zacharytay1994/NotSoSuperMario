#pragma once

#include "GameObject.h"

class Input;
class ColliderManager;
class Mario : public GameObject {
public:
	Sprite* running_animation_;
	Sprite* jumping_animation_;
	bool looking_left = true;
public:
	Mario(Input& input, ColliderManager& cm);
	~Mario();
	void Update(const float& frametime) override;
	void Render() override;
	void ChildInitialize(Graphics& gfx) override;
};