#include "LevelEditor.h"
#include "NotSoSuperMario.h"
#include "LevelOne.h"
#include "MainMenuScreen.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

LevelEditor::LevelEditor(Game* owner)
	:
	Scene(owner),
	tile_(new Sprite("Pictures\\editorempty.png", 16, 16, 9)),
	background1("pictures\\editorbackground.png", 1200, 751, 1, cam_, 0.2f, 0.1f, -300.0f, -650.0f * CAMERA_ZOOM, 10, 10),
	legend_("pictures\\editorlegend.png", 640, 480, 1, cam_, 1.0f, 1.0f, -150, -100, 1, 1)
{
}

LevelEditor::~LevelEditor()
{
}

void LevelEditor::Update(const float& frametime)
{
	Scene::Update(frametime);
	GetGridCoordinatesMouse();

	UpdateCurrentlySelectedTile();
	PlaceTileOnScreen();

	// Drag screen updates
	DragScreen();

	// Update camera stuff
	camera_drag_.Update(frametime);
	graphics_->BindCameraTransform(D3DXVECTOR2(cam_.GetCameraTransform().x_, cam_.GetCameraTransform().y_));
	cam_.Update(frametime);
	
	background1.Update(frametime);
	legend_.Update(frametime);
	legend_.LerpToPosition(frametime);

	// back to main menu
	if (input_->wasKeyPressed(VK_ESCAPE)) {
		graphics_->BindCameraTransform(D3DXVECTOR2(0, 0));
		dynamic_cast<NotSoSuperMario*>(owner_)->ChangeScene(new MainMenu(owner_));
	}
}

void LevelEditor::ChildRender()
{
	background1.Draw();
	legend_.Draw();
	RenderTiles();
	DrawAllScreenStuff();
}

void LevelEditor::BackgroundRender()
{
}

void LevelEditor::Initialize()
{
	tile_->Initialize(*graphics_);
	InitializeGrid();
	camera_drag_.Initialize(*graphics_);
	cam_.SetTarget(&camera_drag_);
	cam_.SetCameraBounds(50, 50, 16 * 50, 16 * 50);

	// initializing font
	currently_selected_block_ = new Font("pictures\\Fixedsys16x28.png", *graphics_, cam_);
	legend_text_ = new Font("pictures\\Fixedsys16x28.png", *graphics_, cam_);
	comment_text_ = new Font("pictures\\Fixedsys16x28.png", *graphics_, cam_);
	font_initialized_ = true;
	background1.Initialize(*graphics_);
	legend_.Initialize(*graphics_);
	legend_.ForceUpdate(false);
	Scene::Initialize();
}

void LevelEditor::InitializeGrid()
{
	for (int x = 0; x < grid_width_; x++) {
		for (int y = 0; y < grid_height_; y++) {
			grid_.push_back(static_cast<BlockTypes>(0));
		}
	}
}

void LevelEditor::GetGridCoordinatesMouse()
{
	 // mouse position
	Vec2<float> updated_dimensions = Vec2<float>(0.0f, 0.0f);
	graphics_->GetWindowRectangle(updated_dimensions);
	int mouse_x = (int)(((float)input_->getMouseX() / updated_dimensions.x_) * (float)GAME_WIDTH) - cam_.GetCameraTransform().x_;
	int mouse_y = (int)(((float)input_->getMouseY() / updated_dimensions.y_) * (float)GAME_HEIGHT) - cam_.GetCameraTransform().y_;

	 // coordinates
	int cell_x = int((float)mouse_x / ((float)grid_width_ * cell_size_) * grid_width_);
	int cell_y = int((float)mouse_y / ((float)grid_height_ * cell_size_) * grid_height_);
	current_grid_coordinates_ = Vec2<int>(cell_x, cell_y);
	/*std::stringstream ss;
	ss << cell_x << "," << cell_y << std::endl;
	OutputDebugString(ss.str().c_str());*/
}

void LevelEditor::RenderTiles()
{
	for (int x = 0; x < grid_width_; x++) {
		for (int y = 0; y < grid_height_; y++) {
			switch (grid_[x * grid_width_ + y]) {
			case BlockTypes::Empty:
				tile_->GetImage().setCurrentFrame(0);
				break;
			case BlockTypes::Block:
				tile_->GetImage().setCurrentFrame(1);
				break;
			case BlockTypes::Mario:
				tile_->GetImage().setCurrentFrame(2);
				break;
			case BlockTypes::Flag:
				tile_->GetImage().setCurrentFrame(3);
				break;
			case BlockTypes::Coin:
				tile_->GetImage().setCurrentFrame(4);
				break;
			case BlockTypes::Goomba:
				tile_->GetImage().setCurrentFrame(5);
				break;
			case BlockTypes::Kappa:
				tile_->GetImage().setCurrentFrame(6);
				break;
			case BlockTypes::Question:
				tile_->GetImage().setCurrentFrame(7);
				break;
			case BlockTypes::Bouncy:
				tile_->GetImage().setCurrentFrame(8);
				break;
			}
			tile_->GetImage().setX(x * cell_size_);
			tile_->GetImage().setY(y * cell_size_);
			tile_->Draw();
		}
	}
}

void LevelEditor::DragScreen()
{
	if (input_->getMouseRButton() && !mouse_lock_) {
		lock_position_ = Vec2<int>(input_->getMouseX(), input_->getMouseY());
		mouse_lock_ = true;
	}
	if (mouse_lock_) {
		// unlock position
		Vec2<int> unlock_position = Vec2<int>(input_->getMouseX(), input_->getMouseY());
		// calculate distance moved
		Vec2<int> distance_moved = lock_position_ - unlock_position;
		// apply distance moved to camera_drag_
		camera_drag_.SetPosition(camera_drag_.GetPosition().x + distance_moved.x_, camera_drag_.GetPosition().y + distance_moved.y_);
		// update old lock position
		lock_position_ = unlock_position;
	}
	if (!input_->getMouseRButton() && mouse_lock_) {
		mouse_lock_ = false;
	}
}

void LevelEditor::UpdateCurrentlySelectedTile()
{
	if (input_->wasKeyPressed('E')) {
		current_block_ = BlockTypes::Empty;
		block_name_ = "Empty";
	}
	else if (input_->wasKeyPressed('B')) {
		current_block_ = BlockTypes::Block;
		block_name_ = "Block";
	}
	else if (input_->wasKeyPressed('M')) {
		current_block_ = BlockTypes::Mario;
		block_name_ = "Mario";
	}
	else if (input_->wasKeyPressed('F')) {
		current_block_ = BlockTypes::Flag;
		block_name_ = "Flag";
	}
	else if (input_->wasKeyPressed('C')) {
		current_block_ = BlockTypes::Coin;
		block_name_ = "Coin";
	}
	else if (input_->wasKeyPressed('G')) {
		current_block_ = BlockTypes::Goomba;
		block_name_ = "Goomba";
	}
	else if (input_->wasKeyPressed('K')) {
		current_block_ = BlockTypes::Kappa;
		block_name_ = "Koopa Troopa";
	}
	else if (input_->wasKeyPressed('Q')) {
		current_block_ = BlockTypes::Question;
		block_name_ = "? Block";
	}
	else if (input_->wasKeyPressed('B')) {
		current_block_ = BlockTypes::Bouncy;
		block_name_ = "Bouncy Block";
	}
	/*if (input_->wasKeyPressed(VK_RETURN)) {
		WriteToTesting();
	}*/
	if (input_->wasKeyPressed('T')) {
		// trigger test checks
		TriggerTest();
	}
}

void LevelEditor::UpdateAllScreenThings()
{
}

void LevelEditor::DrawAllScreenStuff()
{
	if (font_initialized_) {
		// Draw currently selected block
		currently_selected_block_->DrawTextString("Currently Selected: " + block_name_, Vec2<int>(10, GAME_HEIGHT - 60), *graphics_);
		// Draw legend
		/*int legend_x = 10;
		int legend_y = 40;
		int legend_increment = 30;
		legend_text_->DrawTextString("Click on:", Vec2<int>(legend_x, legend_y + legend_increment * 0), *graphics_);
		legend_text_->DrawTextString("Test (T)", Vec2<int>(legend_x, legend_y + legend_increment * 1), *graphics_);
		legend_text_->DrawTextString("Empty (E)", Vec2<int>(legend_x, legend_y + legend_increment * 2), *graphics_);
		legend_text_->DrawTextString("Block (B)", Vec2<int>(legend_x, legend_y + legend_increment * 3), *graphics_);*/
		// Draw comment
		comment_text_->DrawTextString("Note: " + comment_string_, Vec2<int>(10,  GAME_HEIGHT - 30), *graphics_);
	}
}

void LevelEditor::PlaceTileOnScreen()
{
	if (input_->getMouseLButton()) {
		if (current_grid_coordinates_.x_ > grid_width_ - 1 || current_grid_coordinates_.x_ < 0 || current_grid_coordinates_.y_ > grid_height_ - 1 || current_grid_coordinates_.y_ < 0) {
			return;
		}
		// remove old mario if exists
		if (current_block_ == BlockTypes::Mario && mario_initialized_) {
			grid_[mario_position_.x_ * grid_width_ + mario_position_.y_] = BlockTypes::Empty;
			mario_position_ = current_grid_coordinates_;
		}
		// record mario position if first added
		else if (current_block_ == BlockTypes::Mario && !mario_initialized_) {
			mario_position_ = current_grid_coordinates_;
			mario_initialized_ = true;
		}
		// remove old flag if exists
		if (current_block_ == BlockTypes::Flag && flag_initialized_) {
			grid_[flag_position_.x_ * grid_width_ + flag_position_.y_] = BlockTypes::Empty;
			flag_position_ = current_grid_coordinates_;
		}
		// record flag position if first added
		else if (current_block_ == BlockTypes::Flag && !flag_initialized_) {
			flag_position_ = current_grid_coordinates_;
			flag_initialized_ = true;
		}
		// if mario position is compromised set stuff
		if (current_block_ != BlockTypes::Mario) {
			if (current_grid_coordinates_.x_ == mario_position_.x_ && current_grid_coordinates_.y_ == mario_position_.y_) {
				mario_initialized_ = false;
			}
		}
		// if flag position is compromised set stuff
		if (current_block_ != BlockTypes::Flag) {
			if (current_grid_coordinates_.x_ == flag_position_.x_ && current_grid_coordinates_.y_ == flag_position_.y_) {
				flag_initialized_ = false;
			}
		}

		grid_[current_grid_coordinates_.x_ * grid_width_ + current_grid_coordinates_.y_] = current_block_;
	}
}

void LevelEditor::WriteToTesting()
{
	std::ofstream editor_file("Levels/editortesting.txt");
	if (editor_file.is_open()) {
		for (int x = 0; x < grid_width_; x++) {
			for (int y = 0; y < grid_height_; y++) {
				char c = ' ';
				switch (grid_[y * grid_height_ + x]) {
				case BlockTypes::Empty:
					c = 'e';
					break;
				case BlockTypes::Block:
					c = 'x';
					break;
				case BlockTypes::Mario:
					c = 'm';
					break;
				case BlockTypes::Flag:
					c = 'f';
					break;
				case BlockTypes::Coin:
					c = 'c';
					break;
				case BlockTypes::Goomba:
					c = 'g';
					break;
				case BlockTypes::Kappa:
					c = 'k';
					break;
				case BlockTypes::Question:
					c = 'q';
					break;
				case BlockTypes::Bouncy:
					c = 'b';
					break;
				}
				editor_file << c;
			}
			editor_file << "\n";
		}
	}
	editor_file.close();
}

void LevelEditor::TriggerTest()
{
	if (!mario_initialized_ && !flag_initialized_) {
		comment_string_ = "Mario and Flag not Set!";
	}
	else if (!mario_initialized_) {
		comment_string_ = "Mario not set!";
	}
	else if (!flag_initialized_) {
		comment_string_ = "Flag not set!";
	}
	else {
		comment_string_ = "";
		WriteToTesting();
		LevelOne* temp = new LevelOne(owner_, "Levels/editortesting.txt");
		temp->SetTesting(true, this);
		dynamic_cast<NotSoSuperMario*>(owner_)->ChangeSceneNonDelete(temp);
	}
}

void LevelEditor::PublishLevel(const std::string& name)
{
	// create and write to new file
	std::ofstream new_file("Levels/" + name + ".txt");
	if (new_file.is_open()) {
		for (int x = 0; x < grid_width_; x++) {
			for (int y = 0; y < grid_height_; y++) {
				char c = ' ';
				switch (grid_[y * grid_height_ + x]) {
				case BlockTypes::Empty:
					c = 'e';
					break;
				case BlockTypes::Block:
					c = 'x';
					break;
				case BlockTypes::Mario:
					c = 'm';
					break;
				case BlockTypes::Flag:
					c = 'f';
					break;
				}
				new_file << c;
			}
			new_file << "\n";
		}
	}
	new_file.close();
	// add level to level data
	std::ofstream level_data("Levels/leveldata.txt", std::ios_base::app);
	if (level_data.is_open()) {
		level_data << "\n" + name + ".txt";
	}
	level_data.close();
}
