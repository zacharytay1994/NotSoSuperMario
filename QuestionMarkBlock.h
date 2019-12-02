#pragma once

#include "ColliderManager.h"
#include "CollisionDetectionComponent.h"
#include "GameObject.h"
#include "Mario.h"
#include "PhysicsComponent.h"
#include "Scene.h"
#include "Goomba.h"

class QuestionMarkBlock : public GameObject
{
private:
	ColliderManager* cm_;
	Mario* mario_;
	PhysicsComponent* phy_;
	Scene* scene_;

	Sprite* used_sprite_;

	bool used_ = false;
public:
	QuestionMarkBlock(ColliderManager& cm, const Vec2<float>& position, Scene& s, Mario& m);
	void Update(const float& frametime) override;
	void Render() override;
	void ChildInitialize(Graphics& gfx) override;
};