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

	float direction_ = 0.0f;
	float speed_ = 50.0f;
	bool isTouchedMushroom = false;
	bool is_growing_sound_played_ = false;

public:
	Mushroom(ColliderManager& cm, const Vec2<float>& position, Mario& m);
	void Update(const float& frametime) override;
	void Render() override;
	void ChildInitialize(Graphics& gfx) override;
};