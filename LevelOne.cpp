#include "Coin.h"
#include "Flag.h"
#include "Goomba.h"
#include "KoopaTroopa.h"
#include "LevelEditor.h"
#include "LevelSelect.h"
#include "LevelOne.h"
#include "MainMenuScreen.h"
#include "Mario.h"
#include "MarioGhost.h"
#include "NotSoSuperMario.h"
#include "pausedMenu.h"
#include "leaderboard.h"
#include "TestObject.h"

#include <iostream>

using namespace std;

LevelOne::LevelOne(Game* owner, const std::string& filename)
	:
	Scene(owner),
	map_generator_(filename),
	current_level_(filename),
	background5("pictures\\editorbackground.png", 1200, 751, 1, camera_, 0.2f, 0.1f, -300.0f, -1200.0f * CAMERA_ZOOM, 10, 10),
	background4("pictures\\mountainbackground.png", 1200, 1200, 1, camera_, 0.5f, 0.1f, -300.0f, -1200.0f * CAMERA_ZOOM, 10, 1),
	background3("pictures\\cloudbackground.png", 1200, 1200, 1, camera_, 0.4f, 0.1f, -300.0f, -1200.0f * CAMERA_ZOOM, 10, 1),
	background2("pictures\\rockbackground.png", 1200, 1200, 1, camera_, 0.3f, 0.1f, -300.0f, -1200.0f * CAMERA_ZOOM, 10, 1),
	background1("pictures\\bushesbackground.png", 1200, 700, 1, camera_, 0.2f, 0.1f, -300.0f, -650.0f * CAMERA_ZOOM, 10, 1),
	pausedMenu_(new pausedMenu(&camera_)),
	timer_(new Timer()),
	isPaused(false),
	filename_(filename)
{
}

LevelOne::~LevelOne()
{
	delete graphics_;
	delete input_;
	graphics_ = nullptr;
	input_ = nullptr;
}

void LevelOne::Update(const float& frametime)
{
	if (!isPaused && !(mario_->deathAnimationDone))
	{
		// Do not update the frame when the game is paused or mario is dead
		if (input_->wasKeyPressed(VK_ESCAPE)) { isPaused = true; }

		Scene::Update(frametime);
		camera_.Update(frametime);
		graphics_->BindCameraTransform(D3DXVECTOR2(camera_.GetCameraTransform().x_, camera_.GetCameraTransform().y_));
		background4.Update(frametime);
		background3.Update(frametime);
		background2.Update(frametime);
		background1.Update(frametime);

		// Update editor's background if the level is being tested
		if (is_testing_) { background5.Update(frametime); }

		if (!is_testing_) 
		{
			save_mario_.Update(frametime);
			load_mario_.Update(frametime);
		}
		
		TestingUpdate();

		timer_->Update();
	}

	// Stop timer when level is completer
	if (levelCompleted) { timer_->StopTimer(); }

	if (levelCompleted && !showleaderboard_ && !is_testing_) { showleaderboard_ = true; }

	if (showleaderboard_) {
		if (!leaderboard_->HasScore()) {
			leaderboard_->InsertScore(score_manager_->GetScore());
		}
		if (input_->wasKeyPressed(VK_RETURN) && leaderboard_->top10shown_) {
			graphics_->BindCameraTransform(D3DXVECTOR2(0, 0));
			dynamic_cast<NotSoSuperMario*>(owner_)->ChangeScene(new MainMenu(owner_));
		}
		leaderboard_->Update(frametime);
	}

	if (isPaused)
	{
		pausedMenu_->Update(frametime);

		if (is_testing_)
		{
			if (input_->wasKeyPressed(VK_RETURN))
			{
				timer_->StopTimer();
				timer_->PausedDuration();

				if (pausedMenu_->selectionValue() == 0)
				{
					isPaused = false;
					timer_->ContinueTimer();
				}
				else if (pausedMenu_->selectionValue() == 1)
				{
					dynamic_cast<NotSoSuperMario*>(owner_)->ChangeScene(held_scene_);
				}
				else if (pausedMenu_->selectionValue() == 2)
				{
					graphics_->BindCameraTransform(D3DXVECTOR2(0, 0));
					dynamic_cast<NotSoSuperMario*>(owner_)->ChangeScene(new MainMenu(owner_));
				}
			}
		}
		else
		{
			if (input_->wasKeyPressed(VK_RETURN))
			{
				timer_->StopTimer();
				timer_->PausedDuration();

				if (pausedMenu_->selectionValue() == 0)
				{
					isPaused = false;
					timer_->ContinueTimer();
				}
				else if (pausedMenu_->selectionValue() == 1)
				{
					dynamic_cast<NotSoSuperMario*>(owner_)->ChangeScene(new LevelOne(owner_, current_level_));
				}
				else if (pausedMenu_->selectionValue() == 2)
				{
					graphics_->BindCameraTransform(D3DXVECTOR2(0, 0));
					dynamic_cast<NotSoSuperMario*>(owner_)->ChangeScene(new MainMenu(owner_));
				}
			}
		}

	}

	if (mario_->is_dead_)
	{ 
		timer_->StopTimer(); 

		if (mario_->deathAnimationDone)
		{
			if (!is_testing_) {
				graphics_->BindCameraTransform(D3DXVECTOR2(0, 0));
				dynamic_cast<NotSoSuperMario*>(owner_)->ChangeScene(new MainMenu(owner_));
			}
			else {
				dynamic_cast<NotSoSuperMario*>(owner_)->ChangeScene(held_scene_);
			}
		}
	}

	// win actions
	if (levelCompleted && !is_testing_ && !state_recorded_) {
		if (score_manager_->GetScore() < loaded_high_score_) {
			WriteHighScore(score_manager_->GetScore());
			save_mario_.WritePositionToFile();
		}
		state_recorded_ = true;
	}

	if (mario_->GetPosition().y > 50) {
		mario_->isTouchedGoomba = true;
	}
}

void LevelOne::ChildRender()
{
	// by default render on Scene.h is called every frame which will render the gameobjects
	// Draw score
	score_manager_->Draw();
	TestingDraw();

	// If the game is paused, show the paused menu
	if (isPaused)
	{
		pausedMenu_->showMenu();
		pausedMenu_->ChildRender(is_testing_);
	}

	// If mario is dead and the dead animation is done, show the  menu
	if (mario_->isTouchedGoomba)
	{
		if (mario_->deathAnimationDone)
		{
			pausedMenu_->showMenu();
			pausedMenu_->ChildRender(is_testing_);
		}
	}

	if (showleaderboard_) {
		leaderboard_->Render();
	}
}

void LevelOne::BackgroundRender()
{
	background4.Draw();
	background3.Draw();
	background2.Draw();
	background1.Draw();

	// Draw editor's background above everything if the level is being tested
	if (is_testing_) { background5.Draw(); };
}

void LevelOne::Initialize()
{
	// Place to initialize and add objects to scene ----------------------------------------
	Mario* temp = new Mario(*input_, collider_manager_);
	mario_ = temp;
	camera_.SetTarget(temp);
	camera_.SetCameraBounds(50, -64 * CAMERA_ZOOM * 50 - 100, 1600, -250);

	if (!isStart)
	{
		startTime = clock();
		timer_->StartTimer(startTime);
		isStart = true;
	}
	MarioGhost* mario_ghost = new MarioGhost();
	save_mario_.BindMario(temp);
	save_mario_.StartRecording(true);
	load_mario_.BindMario(mario_ghost);
	game_objects_.push_back(mario_ghost);

	// Add scoremanager
	score_manager_ = new ScoreManager(*graphics_, camera_, *timer_);
	map_generator_.GenerateWalls(collider_manager_, game_objects_, *score_manager_, *this, *temp);
	game_objects_.push_back(temp);
	temp->SetPosition(map_generator_.GetMarioPosition().x_, map_generator_.GetMarioPosition().y_);

	leaderboard_ = new Leaderboard(*graphics_, camera_, filename_);

	// Initialize backgrounds
	background5.Initialize(*graphics_);
	background4.Initialize(*graphics_);
	background3.Initialize(*graphics_);
	background2.Initialize(*graphics_);
	background1.Initialize(*graphics_);

	pausedMenu_->Initialize(*graphics_, input_);
	leaderboard_->Initialize(*graphics_, input_);

	// Initialize fonts
	options_display_ = new Font("pictures\\Fixedsys16x28.png", *graphics_, camera_);
	name_display_ = new Font("pictures\\Fixedsys16x28.png", *graphics_, camera_);
	// -------------------------------------------------------------------------------------
	// Initializing ghost and score
	InitGhostData();
	Scene::Initialize();
}

void LevelOne::TestingUpdate()
{
	if (!is_testing_) {
		return;
	}
	if (levelCompleted) {
		display_options_ = true;
	}
	if (display_options_) {
		if (input_->wasKeyPressed('P')) {
			is_writing_ = true;
		}
		else if (input_->wasKeyPressed('C')) {
			dynamic_cast<NotSoSuperMario*>(owner_)->ChangeScene(held_scene_);
		}
		else if (input_->wasKeyPressed(VK_ESCAPE)) {
			graphics_->BindCameraTransform(D3DXVECTOR2(0, 0));
			dynamic_cast<NotSoSuperMario*>(owner_)->ChangeScene(new MainMenu(owner_));
		}
	}
	if (is_writing_) {
		if (input_->wasKeyPressed(VK_RETURN)) {
			dynamic_cast<LevelEditor*>(held_scene_)->PublishLevel(name_in_);

			graphics_->BindCameraTransform(D3DXVECTOR2(0, 0));
			dynamic_cast<NotSoSuperMario*>(owner_)->ChangeScene(new LevelSelect(owner_));
		}
	}
}

void LevelOne::TestingDraw()
{
	if (!is_testing_) {
		return;
	}
	if (display_options_) {
		options_display_->DrawTextString("CONGRATS YOU HAVE BEATEN YOUR CREATION!", Vec2<int>(10, GAME_HEIGHT / 2 - 30), *graphics_);
		options_display_->DrawTextString("C = Continue Editing", Vec2<int>(10, GAME_HEIGHT/2), *graphics_);
		options_display_->DrawTextString("P = Publish Level", Vec2<int>(10, GAME_HEIGHT / 2 + 30), *graphics_);
		options_display_->DrawTextString("E = Exit to Main Menu", Vec2<int>(10, GAME_HEIGHT / 2 + 60), *graphics_);
	}
	RenderWriting();
}

void LevelOne::SetTesting(const bool& test, Scene* scene)
{
	is_testing_ = test;
	held_scene_ = scene;
}

void LevelOne::RenderWriting()
{
	if (is_writing_) {
		name_display_->DrawTextString("-- Key In Your Level Name & Enter --", Vec2<int>(10, GAME_HEIGHT / 2 - 120), *graphics_);
		name_display_->DrawTextString(name_in_, Vec2<int>(10, GAME_HEIGHT / 2 - 150), *graphics_);
		name_in_ = input_->getTextIn();
		if (clear_name_ && name_in_ != "") {
			input_->clearTextIn();
			clear_name_ = false;
		}
	}
}

void LevelOne::InitGhostData()
{
	// get file name
	std::string name = current_level_.substr(current_level_.find("/") + 1, current_level_.find(".") - current_level_.find("/") - 1);
	// Get existing highscore
	std::ifstream high_score_file("ScoreRecords/" + name + "highscore.txt");
	std::string line;
	if (high_score_file.is_open()) {
		while (std::getline(high_score_file, line)) {
			loaded_high_score_ = (float)std::stoi(line) / 1000.0f;
		}
		score_manager_->SetScoreToBeat(loaded_high_score_);
	}
	// Get ghost record file
	load_mario_.SetFilename("ScoreRecords/" + name + "ghost.txt");
	load_mario_.ReadPositions();
	save_mario_.SetFilename("ScoreRecords/" + name + "ghost.txt");
}

void LevelOne::WriteHighScore(const float& score)
{
	std::string name = current_level_.substr(current_level_.find("/") + 1, current_level_.find(".") - current_level_.find("/") - 1);
	std::ofstream high_score_file("ScoreRecords/" + name + "highscore.txt");
	if (high_score_file.is_open()) {
		high_score_file << score * 1000;
	}
	high_score_file.close();
}
