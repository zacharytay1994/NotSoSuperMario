#pragma once

#include "ColliderManager.h"
#include "GameObject.h"
#include "input.h"
#include "PhysicsComponent.h"

class Coin : public GameObject
{
private:
	PhysicsComponent* phy_;
public:
	Coin(Input& input, ColliderManager& cm, const Vec2<float>& position);
	void Update(const float& frametime) override;
	void Render() override;
	void ChildInitialize(Graphics& gfx) override;
};