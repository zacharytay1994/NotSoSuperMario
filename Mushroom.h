#pragma once

#include "ColliderManager.h"
#include "CollisionDetectionComponent.h"
#include "GameObject.h"
#include "Mario.h"
#include "PhysicsComponent.h"

class Mushroom : public GameObject 
{
private:
	ColliderManager* cm_;
	Mario* mario_;
	PhysicsComponent* phy_;

public:
	Mushroom(ColliderManager& cm, const Vec2<float>& position, Mario& m);
	void Update(const float& frametime) override;
	void Render() override;
	void ChildInitialize(Graphics& gfx) override;
};