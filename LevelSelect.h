#pragma once
#include "Scene.h"
#include "Font.h"
#include "Camera.h"
#include "Sprite.h"
#include "Vec2.h"
#include <string>
#include <filesystem>
#include <vector>

class Graphics;
class LevelSelect : public Scene {
private:
	Camera cam_;
	// folder path name
	std::string level_folder_ = "Levels/";
	// level data file
	std::string level_data_ = "leveldata.txt";
	// level name container
	std::vector<std::string> level_data_array;
	std::string currently_selected_level;
	int indexed_level = 1;
	int num_levels_ = 0;
	std::string selected_name_ = "";
	std::string bottom_name_ = "";
	std::string top_name_ = "";
	Font* font_display_;
	Font* font_display_top_;
	Font* font_display_bot_;
	bool font_initialized_ = false;
	bool ready_ = false;
	Sprite* background_;

	// word placement variables
	Vec2<int> selected_pos_ = Vec2<int>(50, (int)(GAME_HEIGHT/2 - 10));
	Vec2<int> bottom_pos_ = Vec2<int>(50, (int)(GAME_HEIGHT / 2 + 80));
	Vec2<int> top_pos_ = Vec2<int>(50, (int)(GAME_HEIGHT / 2 - 100));
public:
	LevelSelect(Game* owner);
	~LevelSelect();
	void Update(const float& frametime) override;
	void ChildRender() override;
	void BackgroundRender() override;
	void Initialize() override;
	void ReadAllLevelsFromFolder();
	void ReadAllLevelsToVector();
	void UpdateSelectedNames(const bool& some);
};