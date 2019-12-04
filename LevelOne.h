#pragma once
#include "Scene.h"
#include "ColliderManager.h"
#include "Camera.h"
#include "MapGenerator.h"
#include "Background.h"
#include "ScoreManager.h"

class LevelOne : public Scene {
public:
	ColliderManager collider_manager_;
	Camera camera_;
	MapGenerator map_generator_;
	Background background4;
	Background background3;
	Background background2;
	Background background1;
	ScoreManager* score_manager_;
	pausedMenu* pausedMenu_;
	bool isPaused;
	bool levelCompleted = false;
public:
	LevelOne(Game* owner);
	~LevelOne();
	void Update(const float& frametime) override;
	void ChildRender() override;
	void BackgroundRender() override;
	void Initialize() override;
};