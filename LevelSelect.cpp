#include "LevelSelect.h"
#include "NotSoSuperMario.h"
#include "LevelOne.h"
#include <iostream>
#include <sstream>
#include <fstream>

LevelSelect::LevelSelect(Game* owner)
	:
	Scene(owner),
	background_(new Sprite("pictures\\levelselectbackground.png", 640, 480, 1))
{
	ReadAllLevelsToVector();
}

LevelSelect::~LevelSelect()
{
}

void LevelSelect::Update(const float& frametime)
{
	UpdateSelectedNames(false);
}

void LevelSelect::ChildRender()
{
	background_->Draw();
	if (font_initialized_) {
		std::ostringstream ss;
		std::ostringstream ss1;
		std::ostringstream ss2;

		ss << selected_name_;
		ss1 << bottom_name_;
		ss2 << top_name_;

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
	font_display_ = new Font("pictures\\Fixedsys16x28.png", *graphics_, cam_);
	font_display_top_ = new Font("pictures\\Fixedsys16x28.png", *graphics_, cam_);
	font_display_bot_ = new Font("pictures\\Fixedsys16x28.png", *graphics_, cam_);
	background_->Initialize(*graphics_);
	font_initialized_ = true;
	UpdateSelectedNames(true);
	ready_ = true;
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
				if (indexed_level + 1 >= 0) {
					bottom_name_ = level_data_array[indexed_level + 1];
				}
				else {
					bottom_name_ = "";
				}
				if (indexed_level - 1 >= 0) {
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
