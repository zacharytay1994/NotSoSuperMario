#include "LevelOne.h"
#include "Coin.h"
#include "Mario.h"
#include "Goomba.h"
#include "TestObject.h"
#include "Flag.h"
#include <iostream>
#include "NotSoSuperMario.h"
#include "pausedMenu.h"
#include "MainMenuScreen.h"
using namespace std;

LevelOne::LevelOne(Game* owner)
	:
	Scene(owner),
	map_generator_("levelone.txt"),
	background4("pictures\\mountainbackground.png", 1200, 1200, 1, camera_, 0.5f, 0.1f, -300.0f, -400.0f, 10, 1),
	background3("pictures\\cloudbackground.png", 1200, 1200, 1, camera_, 0.4f, 0.1f, -300.0f, -300.0f, 10, 1),
	background2("pictures\\rockbackground.png", 1200, 1200, 1, camera_, 0.3f, 0.1f, -300.0f, -200.0f, 10, 1),
	background1("pictures\\bushesbackground.png", 1200, 700, 1, camera_, 0.2f, 0.1f, -300.0f, 100.0f, 10, 1),
	pausedMenu_(new pausedMenu(&camera_)),
	timer_(new Timer()),
	isPaused(false)
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

		timer_->Update();
	}

	if (isPaused)
	{
		pausedMenu_->Update(frametime);

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
				dynamic_cast<NotSoSuperMario*>(owner_)->ChangeScene(new LevelOne(owner_));
			}
			else if (pausedMenu_->selectionValue() == 2)
			{
				graphics_->BindCameraTransform(D3DXVECTOR2(0, 0));
				dynamic_cast<NotSoSuperMario*>(owner_)->ChangeScene(new MainMenu(owner_));
			}
		}
	}

	if (mario_->isDead) 
	{ 
		timer_->StopTimer(); 

		if (mario_->deathAnimationDone)
		{
			graphics_->BindCameraTransform(D3DXVECTOR2(0, 0));
			dynamic_cast<NotSoSuperMario*>(owner_)->ChangeScene(new MainMenu(owner_));
		}
	}
}

void LevelOne::ChildRender()
{
	// by default render on Scene.h is called every frame which will render the gameobjects
	// Draw score
	score_manager_->Draw();

	// If the game is paused, show the paused menu
	if (isPaused)
	{
		pausedMenu_->showMenu();
		pausedMenu_->ChildRender();	
	}

	// If mario is dead and the dead animation is done, show the  menu
	if (mario_->isDead)
	{
		if (mario_->deathAnimationDone)
		{
			pausedMenu_->showMenu();
			pausedMenu_->ChildRender();
		}
	}
}

void LevelOne::BackgroundRender()
{
	background4.Draw();
	background3.Draw();
	background2.Draw();
	background1.Draw();
}

void LevelOne::Initialize()
{
	// Place to initialize and add objects to scene ----------------------------------------
	Mario* temp = new Mario(*input_, collider_manager_);
	mario_ = temp;
	camera_.SetTarget(temp);

	if (!isStart)
	{
		startTime = clock();
		timer_->StartTimer(startTime);
		isStart = true;
	}

	// Add scoremanager
	score_manager_ = new ScoreManager(*graphics_, camera_, *timer_);
	map_generator_.GenerateWalls(collider_manager_, game_objects_, *score_manager_, *this, *temp);
	game_objects_.push_back(temp);

	background4.Initialize(*graphics_);
	background3.Initialize(*graphics_);
	background2.Initialize(*graphics_);
	background1.Initialize(*graphics_);

	pausedMenu_->Initialize(*graphics_, input_);
	// -------------------------------------------------------------------------------------
	Scene::Initialize();
}
