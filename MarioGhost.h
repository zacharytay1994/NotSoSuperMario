#pragma once
#include "GameObject.h"
#include "Sprite.h"

class MarioGhost: public GameObject {
public:
	Sprite* running_animation_;
	Sprite* jumping_animation_;
public:
	MarioGhost();
	~MarioGhost();
	void Update(const float& frametime) override;
	void Render() override;
	void ChildInitialize(Graphics& gfx) override;
};