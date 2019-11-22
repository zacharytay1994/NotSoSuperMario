#pragma once
#include "input.h"

#include "Scene.h"

class LevelOne : public Scene {
public:
public:
	LevelOne();
	~LevelOne();
	void Update(const float& frametime) override;
	void ChildRender() override;
	void Initialize() override;
};