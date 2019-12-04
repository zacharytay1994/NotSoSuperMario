#pragma once
#include "Scene.h"
#include "ColliderManager.h"
#include "Camera.h"
#include "MapGenerator.h"
#include "Background.h"
#include "ScoreManager.h"
#include "Timer.h"
#include "SaveMario.h"
#include "LoadMario.h"
#include "Font.h"
#include <string>

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
	SaveMario save_mario_;
	LoadMario load_mario_;
	std::string current_level_ = "";

	// flags
	bool is_testing_ = false;
	bool display_options_ = false;
	Font* options_display_;
	Scene* held_scene_;
	bool is_writing_ = false;
	std::string name_in_ = "";
	Font* name_display_;
	bool clear_name_ = true;

	pausedMenu* pausedMenu_;
	Mario* mario_;
	Timer* timer_;
	bool isPaused;
	bool isStart = false;
	std::clock_t startTime;
	bool levelCompleted = false;
public:
	LevelOne(Game* owner, const std::string& filename);
	~LevelOne();
	void Update(const float& frametime) override;
	void ChildRender() override;
	void BackgroundRender() override;
	void Initialize() override;
	void TestingUpdate();
	void TestingDraw();
	void SetTesting(const bool& test, Scene* scene);
	void RenderWriting();
	void SetCurrentLevel(const std::string& level);
};