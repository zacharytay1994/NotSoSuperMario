#pragma once

#include "ColliderManager.h"
#include "GameObject.h"
#include "PhysicsComponent.h"
#include "Scene.h"

class Flag : public GameObject {
private:
	float initialFlagHeight;
	GameObject* mario_;
	Scene* scene_;
	bool touch;
	bool flagdown;
	float contactdistance; // vertical distance between mario contact point and bottom of flagpole
	float flagrelativeposition; // value between 1 and 0, 1 being initialflagheight 
	
public:
	Sprite* flagflag_;

	Flag(ColliderManager& cm, const Vec2<float>& position, GameObject& mario, Scene& scene);

	void Update(const float& frametime) override;
	void Render() override;
	void ChildInitialize(Graphics& gfx) override;

};