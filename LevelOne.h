#pragma once
#include "Scene.h"
#include "ColliderManager.h"

class LevelOne : public Scene {
public:
	ColliderManager collider_manager_;
public:
	LevelOne();
	~LevelOne();
	void Update(const float& frametime) override;
	void ChildRender() override;
	void Initialize() override;
};