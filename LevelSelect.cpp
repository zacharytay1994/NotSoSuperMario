#include "LevelSelect.h"
#include "NotSoSuperMario.h"
#include "MainMenuScreen.h"
#include "LevelOne.h"
#include <iostream>
#include <sstream>
#include <fstream>

LevelSelect::LevelSelect(Game* owner)
	:
	Scene(owner),
	background_(new Sprite("pictures\\levelselectbackground.png", 640, 480, 1)),
	tile_(Sprite("pictures\\editorempty2.png", 9, 9, 9)),
	mexican_mario_(Sprite("pictures\\mexicanmario.png", 640, 480,1)),
	shopfore_(Sprite("pictures\\marioshop.png", 640, 480, 1)),
	shopback_(Sprite("pictures\\marioshop2.png", 640, 480, 1)),
	shoplayer1_(Sprite("pictures\\marioshop3.png", 640, 480, 1)),
	shoplayer2_(Sprite("pictures\\marioshop4.png", 640, 480, 1)),
	shoplayer3_(Sprite("pictures\\marioshop5.png", 640, 480, 1)),
	pseudogoomba1_(Sprite("pictures\\goombawalksheet.png", 64, 64, 4)),
	pseudogoomba2_(Sprite("pictures\\goombawalksheet.png", 64, 64, 4)),
	pseudokoopa_(Sprite("pictures\\kooparunsheet.png", 64, 64, 8))
{
	ReadAllLevelsToVector();
}

LevelSelect::~LevelSelect()
{
}

void LevelSelect::Update(const float& frametime)
{
	UpdateSelectedNames(false);
	CenterGrid();
	AnimateGrid(frametime, 30.0f);
	/*tile_.GetImage().setX(0);
	tile_.GetImage().setY(0);
	tile_.SetCurrentFrame(1);
	tile_.Draw();*/
	pseudogoomba2_.Update(frametime);
	pseudogoomba1_.Update(frametime);
	pseudokoopa_.Update(frametime);
	WalkStuff(frametime);
	// return if escape
	if (input_->wasKeyPressed(VK_ESCAPE)) {
		dynamic_cast<NotSoSuperMario*>(owner_)->ChangeScene(new MainMenu(owner_));
	}
}

void LevelSelect::ChildRender()
{
	shopback_.Draw();
	pseudogoomba2_.Draw();
	shoplayer3_.Draw();
	pseudokoopa_.Draw();
	shoplayer2_.Draw();
	pseudogoomba1_.Draw();
	shoplayer1_.Draw();
	mexican_mario_.Draw();
	shopfore_.Draw();
	background_->Draw();
	RenderDisplayContainer(display_container_);
	if (font_initialized_) {
		std::ostringstream ss;
		std::ostringstream ss1;
		std::ostringstream ss2;

		std::string selected = selected_name_.substr(0, selected_name_.length() - 4);
		std::string top = top_name_.substr(0, top_name_.length() - 4);
		std::string bottom = bottom_name_.substr(0, bottom_name_.length() - 4);
		ss << selected;
		ss1 << bottom;
		ss2 << top;

		font_display_->DrawTextString(ss.str(), selected_pos_, *graphics_);
		font_display_top_->DrawTextString(ss2.str(), top_pos_, *graphics_);
		font_display_bot_->DrawTextString(ss1.str(), bottom_pos_, *graphics_);
	}
}

void LevelSelect::BackgroundRender()
{
}

void LevelSelect::Initialize()
{
	InitializeDisplayContainer();
	font_display_ = new Font("pictures\\Fixedsys16x28.png", *graphics_, cam_);
	font_display_top_ = new Font("pictures\\Fixedsys16x28.png", *graphics_, cam_);
	font_display_bot_ = new Font("pictures\\Fixedsys16x28.png", *graphics_, cam_);
	background_->Initialize(*graphics_);
	font_initialized_ = true;
	UpdateSelectedNames(true);
	tile_.Initialize(*graphics_);
	mexican_mario_.Initialize(*graphics_);
	shopfore_.Initialize(*graphics_);
	shopback_.Initialize(*graphics_);
	shoplayer1_.Initialize(*graphics_);
	shoplayer2_.Initialize(*graphics_);
	shoplayer3_.Initialize(*graphics_);
	ready_ = true;

	// init mob sprite
	pseudogoomba1_.Initialize(*graphics_);
	pseudogoomba1_.InitializeAnimation(0, 5, 0.25);
	pseudogoomba1_.GetImage().setX(GAME_WIDTH / 2);
	pseudogoomba1_.GetImage().setY(GAME_HEIGHT/2 + 20);
	pseudogoomba2_.Initialize(*graphics_);
	pseudogoomba2_.InitializeAnimation(0, 5, 0.25);
	pseudogoomba2_.GetImage().setX(GAME_WIDTH / 2);
	pseudogoomba2_.GetImage().setY(GAME_HEIGHT / 2 + 5);
	pseudogoomba2_.GetImage().flipHorizontal(true);
	pseudokoopa_.Initialize(*graphics_);
	pseudokoopa_.InitializeAnimation(0, 7, 0.25);
	pseudokoopa_.GetImage().setX(64);
	pseudokoopa_.GetImage().setY(GAME_HEIGHT/2 + 5);
	pseudokoopa_.GetImage().flipHorizontal(true);
	Scene::Initialize();
}

void LevelSelect::ReadAllLevelsFromFolder()
{
}

void LevelSelect::ReadAllLevelsToVector()
{
	std::ifstream level_dat(level_folder_ + level_data_);
	if (level_dat.is_open()) {
		std::string line;
		while (std::getline(level_dat, line)) {
			level_data_array.push_back(line);
		}
	}
	num_levels_ = level_data_array.size();
}

void LevelSelect::UpdateSelectedNames(const bool& some)
{
	if (font_initialized_) {
		if (input_->wasKeyPressed(VK_DOWN)) {
			if (indexed_level < num_levels_ - 1) {
				indexed_level++;
				selected_name_ = level_data_array[indexed_level];
				ReadAndUpdateDisplayContainer("Levels/" + selected_name_, display_container_);
				if (indexed_level + 1 < num_levels_) {
					bottom_name_ = level_data_array[indexed_level + 1];
				}
				else {
					bottom_name_ = "";
				}
				if (indexed_level - 1 < num_levels_ - 1) {
					top_name_ = level_data_array[indexed_level - 1];
				}
				else {
					top_name_ = "";
				}
			}
		}
		if (input_->wasKeyPressed(VK_UP) || some) {
			if (indexed_level > 0) {
				indexed_level--;
				selected_name_ = level_data_array[indexed_level];
				ReadAndUpdateDisplayContainer("Levels/" + selected_name_, display_container_);
				if (indexed_level + 1 >= 0 && indexed_level + 1 < level_data_array.size()) {
					bottom_name_ = level_data_array[indexed_level + 1];
				}
				else {
					bottom_name_ = "";
				}
				if (indexed_level - 1 >= 0 && indexed_level - 1 < level_data_array.size()) {
					top_name_ = level_data_array[indexed_level - 1];
				}
				else {
					top_name_ = "";
				}
			}
		}
		if (input_->wasKeyPressed(VK_RETURN) && ready_) {
			LevelOne* temp = new LevelOne(owner_, level_folder_ + selected_name_);
			dynamic_cast<NotSoSuperMario*>(owner_)->ChangeScene(temp);
		}
	}
}

void LevelSelect::InitializeDisplayContainer()
{
	// hard coded! suck it!
	for (int x = 0; x < 50; x++) {
		for (int y = 0; y < 50; y++) {
			display_container_.push_back(BlockType::Empty);
		}
	}
}

void LevelSelect::ReadAndUpdateDisplayContainer(const std::string& path, std::vector<BlockType>& container)
{
	int start_x = 0;
	int start_y = 0;
	std::ifstream file(path);
	std::string line;
	while (std::getline(file, line)) {
		for each (char c in line) {
			if (c == 'e') {
				container[start_x * grid_width_ + start_y] = BlockType::Empty;
			}
			else if (c == 'x') {
				container[start_x * grid_width_ + start_y] = BlockType::Block;
			}
			else if (c == 'c') {
				container[start_x * grid_width_ + start_y] = BlockType::Coin;
			}
			else if (c == 'g') {
				container[start_x * grid_width_ + start_y] = BlockType::Goomba;
			}
			else if (c == 'q') {
				container[start_x * grid_width_ + start_y] = BlockType::Question;
			}
			else if (c == 'b') {
				container[start_x * grid_width_ + start_y] = BlockType::Bouncy;
			}
			else if (c == 'k') {
				container[start_x * grid_width_ + start_y] = BlockType::Kappa;
			}
			else if (c == 'f') {
				container[start_x * grid_width_ + start_y] = BlockType::Flag;
			}
			else if (c == 'm') {
				container[start_x * grid_width_ + start_y] = BlockType::Mario;
			}
			start_x++;
		}
		start_x = 0;
		start_y++;
	}
	file.close();
	cell_size_ = 0.1f;
}

void LevelSelect::RenderDisplayContainer(std::vector<BlockType>& container)
{
	for (int x = 0; x < grid_width_; x++) {
		for (int y = 0; y < grid_height_; y++) {
			switch (container[x * grid_width_ + y]) {
			case BlockType::Empty:
				tile_.GetImage().setCurrentFrame(0);
				break;
			case BlockType::Block:
				tile_.GetImage().setCurrentFrame(1);
				break;
			case BlockType::Mario:
				tile_.GetImage().setCurrentFrame(2);
				break;
			case BlockType::Flag:
				tile_.GetImage().setCurrentFrame(3);
				break;
			case BlockType::Coin:
				tile_.GetImage().setCurrentFrame(4);
				break;
			case BlockType::Goomba:
				tile_.GetImage().setCurrentFrame(5);
				break;
			case BlockType::Kappa:
				tile_.GetImage().setCurrentFrame(6);
				break;
			case BlockType::Question:
				tile_.GetImage().setCurrentFrame(7);
				break;
			case BlockType::Bouncy:
				tile_.GetImage().setCurrentFrame(8);
				break;
			}
			tile_.GetImage().setX(grid_offset_x_ + x * cell_size_);
			tile_.GetImage().setY(grid_offset_y_ + y * cell_size_);
			tile_.Draw();
		}
	}
}

void LevelSelect::CenterGrid()
{
	grid_offset_x_ = GAME_WIDTH / 2 - grid_width_ / 2 * cell_size_;
	grid_offset_y_ = GAME_HEIGHT / 2 - grid_height_ / 2 * cell_size_;
}

void LevelSelect::AnimateGrid(const float& frametime, const float& animationspeed)
{
	if (cell_size_ < 9.0f) {
		cell_size_ += animationspeed * frametime;
	}
	else {
		cell_size_ = 9.0f;
	}
}

void LevelSelect::WalkStuff(const float& frametime)
{
	if (pseudogoomba1_.GetImage().getX() < 0.0f) {
		pseudogoomba1_.GetImage().flipHorizontal(true);
		walking_speed_ *= -1;
	}
	else if (pseudogoomba1_.GetImage().getX() > GAME_WIDTH - pseudogoomba1_.GetImage().getWidth()) {
		pseudogoomba1_.GetImage().flipHorizontal(false);
		walking_speed_ *= -1;
	}
	if (pseudogoomba2_.GetImage().getX() < 0.0f) {
		pseudogoomba2_.GetImage().flipHorizontal(true);
		walking_speed_3_ *= -1;
	}
	else if (pseudogoomba2_.GetImage().getX() > GAME_WIDTH - pseudogoomba2_.GetImage().getWidth()) {
		pseudogoomba2_.GetImage().flipHorizontal(false);
		walking_speed_3_ *= -1;
	}
	if (pseudokoopa_.GetImage().getX() < 0.0f) {
		pseudokoopa_.GetImage().flipHorizontal(true);
		walking_speed_2_ *= -1;
	}
	else if (pseudokoopa_.GetImage().getX() > GAME_WIDTH - pseudokoopa_.GetImage().getWidth()) {
		pseudokoopa_.GetImage().flipHorizontal(false);
		walking_speed_2_ *= -1;
	}
	pseudogoomba2_.GetImage().setX(pseudogoomba2_.GetImage().getX() + walking_speed_3_ * frametime);
	pseudogoomba1_.GetImage().setX(pseudogoomba1_.GetImage().getX() + walking_speed_ * frametime);
	pseudokoopa_.GetImage().setX(pseudokoopa_.GetImage().getX() + walking_speed_2_ * frametime);
}
