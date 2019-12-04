#pragma once

#include "ColliderManager.h"
#include "GameObject.h"
#include "PhysicsComponent.h"

class Flag : public GameObject {
private:
	float initialFlagHeight;
	GameObject* mario_;
	bool touch;
	bool flagdown;
	float contactdistance; // vertical distance between mario contact point and bottom of flagpole
	float flagrelativeposition; // value between 1 and 0, 1 being initialflagheight 
	
public:
	Sprite* flagflag_;
	Sprite* flagpole_;
	//Sprite* flagfinial_;

	Flag(ColliderManager& cm, const Vec2<float>& position, GameObject* mario);

	void Update(const float& frametime) override;
	void Render() override;
	void ChildInitialize(Graphics& gfx) override;

};