#pragma once
#include "Scene.h"
#include "ColliderManager.h"
#include "Camera.h"
#include "MapGenerator.h"
#include "Background.h"
#include "ScoreManager.h"
#include	"Timer.h"

class Mario;
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
	Mario* mario_;
	Timer* timer_;
	bool isPaused;
	bool isStart = false;
	std::clock_t startTime;
public:
	LevelOne(Game* owner);
	~LevelOne();
	void Update(const float& frametime) override;
	void ChildRender() override;
	void BackgroundRender() override;
	void Initialize() override;
};