#pragma once
#include "Scene.h"
#include "Vec2.h"
#include "Sprite.h"
#include "Camera.h"
#include "GameObject.h"
#include "Font.h"
#include "Background.h"
#include <vector>

enum class BlockTypes {
	Empty,
	Block,
	Mario,
	Flag,
	Coin,
	Goomba,
	Kappa,
	Question,
	Bouncy
};

class LevelEditor : public Scene {
private:
	int cell_size_ = 16;
	int grid_width_ = 50;
	int grid_height_ = 50;
	std::vector<BlockTypes> grid_;
	Vec2<int> current_grid_coordinates_ = Vec2<int>(0, 0);
	Sprite* tile_;
	BlockTypes current_block_ = BlockTypes::Empty;
	std::string block_name_ = "Empty";

	// Camera drag
	Camera cam_;
	GameObject camera_drag_ = GameObject("pictures\\" + theme + "\\marioidle.png", 64, 64, 1, D3DXVECTOR2(0, 50 * CAMERA_ZOOM * 16 + GAME_HEIGHT/2));
	bool mouse_lock_ = false;
	Vec2<int> lock_position_ = Vec2<int>(0, 0);
	Vec2<int> camera_translate_ = Vec2<int>(0, 0);

	// font stuff
	bool font_initialized_ = false;
	Font* currently_selected_block_;
	Font* legend_text_;
	Font* comment_text_;
	std::string comment_string_ = "Publish after succesful testing!";

	// checks
	bool mario_initialized_ = false;
	bool flag_initialized_ = false;
	Vec2<int> mario_position_ = Vec2<int>(0, 0);
	Vec2<int> flag_position_ = Vec2<int>(0, 0);

	// visual niceness
	Background background1;
	Background legend_;

public:
	LevelEditor(Game* owner);
	~LevelEditor();
	void Update(const float& frametime) override;
	void ChildRender() override;
	void BackgroundRender() override;
	void Initialize() override;
	void InitializeGrid();
	void GetGridCoordinatesMouse();
	void RenderTiles();
	void DragScreen();
	void UpdateCurrentlySelectedTile();
	void UpdateAllScreenThings();
	void DrawAllScreenStuff();
	void PlaceTileOnScreen();
	void WriteToTesting();
	void TriggerTest();
	void PublishLevel(const std::string& name);
};