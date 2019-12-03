#pragma once
#include "ColliderManager.h"
#include "GameObject.h"
#include "PhysicsComponent.h"


class BouncyPlatform : public GameObject
{
private:
	PhysicsComponent * phy_;

public:
	//BouncyPlatform(ColliderManager& cm);
	BouncyPlatform(ColliderManager& cm, const Vec2<float>& position);
	//BouncyPlatform(ColliderManager& cm, const float& x, const float& y);
	void Update(const float& frametime) override;
	void Render() override;
	void ChildInitialize(Graphics& gfx) override;
};