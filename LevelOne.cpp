#include "LevelOne.h"
#include "Coin.h"
#include "Mario.h"
#include "Goomba.h"
#include "TestObject.h"
#include "Flag.h"
#include <iostream>
#include "NotSoSuperMario.h"
#include "pausedMenu.h"

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

	if (!isPaused)
	{
		if (input_->wasKeyPressed(VK_ESCAPE))
		{
			isPaused = true;
		}

		Scene::Update(frametime);
		camera_.Update(frametime);
		graphics_->BindCameraTransform(D3DXVECTOR2(camera_.GetCameraTransform().x_, camera_.GetCameraTransform().y_));
		background4.Update(frametime);
		background3.Update(frametime);
		background2.Update(frametime);
		background1.Update(frametime);
	}
	if (isPaused)

	{


			if (input_->wasKeyPressed(VK_RETURN))
			{
				isPaused = false;
			}
		
	}
	
}

void LevelOne::ChildRender()
{
	// by default render on Scene.h is called every frame which will render the gameobjects

	// Draw score
	score_manager_->Draw();
	if (isPaused)
	{
		
			pausedMenu_->showMenu();
			pausedMenu_->ChildRender();
		
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
	camera_.SetTarget(temp);
	game_objects_.push_back(temp);
	/*game_objects_.push_back(new Goomba(*input_, collider_manager_, { 800.0f,200.0f }));
	game_objects_.push_back(new Goomba(*input_, collider_manager_, { 1000.0f,200.0f }));
	game_objects_.push_back(new Goomba(*input_, collider_manager_, { 1200.0f,200.0f }));
	game_objects_.push_back(new Goomba(*input_, collider_manager_, { 1400.0f,200.0f }));
	game_objects_.push_back(new Coin(*input_, collider_manager_, { 400.0f,300.0f }));
	game_objects_.push_back(new Coin(*input_, collider_manager_, { 500.0f,300.0f }));
	game_objects_.push_back(new Coin(*input_, collider_manager_, { 600.0f,300.0f }));
	game_objects_.push_back(new Flag(collider_manager_, { 300.0f, 740.0f },temp));
	game_objects_.push_back(new Goomba(*input_, collider_manager_, { 1400.0f,200.0f }));*/
	/*

	// Add scoremanager
	score_manager_ = new ScoreManager(*graphics_, camera_);
	map_generator_.GenerateWalls(collider_manager_, game_objects_, *score_manager_);

	background4.Initialize(*graphics_);
	background3.Initialize(*graphics_);
	background2.Initialize(*graphics_);
	background1.Initialize(*graphics_);

	pausedMenu_->Initialize(*graphics_);
	
	

	/*game_objects_.push_back(new TestObject(collider_manager_, 320, GAME_HEIGHT - 50));
	for (int i = 1; i < 5; i++) {
		game_objects_.push_back(new TestObject(collider_manager_, 320 + i * 64, GAME_HEIGHT - 50));
		game_objects_.push_back(new TestObject(collider_manager_, 320 - i * 64, GAME_HEIGHT - 50));
	}
	game_objects_.push_back(new TestObject(collider_manager_, 320, 50));
	for (int i = 1; i < 5; i++) {
		game_objects_.push_back(new TestObject(collider_manager_, 320 + i * 64, 50));
		game_objects_.push_back(new TestObject(collider_manager_, 320 - i * 64, 50));
	}
	game_objects_.push_back(new TestObject(collider_manager_, 50, 240));
	game_objects_.push_back(new TestObject(collider_manager_, 114, 240));
	game_objects_.push_back(new TestObject(collider_manager_, 178, 240));
	for (int i = 1; i < 3; i++) {
		game_objects_.push_back(new TestObject(collider_manager_, 50, 240 + i * 64));
		game_objects_.push_back(new TestObject(collider_manager_, 50, 240 - i * 64));
	}
	game_objects_.push_back(new TestObject(collider_manager_, GAME_WIDTH - 50, 240));
	game_objects_.push_back(new TestObject(collider_manager_, GAME_WIDTH - 178, 240));
	game_objects_.push_back(new TestObject(collider_manager_, GAME_WIDTH - 242, 240));
	for (int i = 1; i < 3; i++) {
		game_objects_.push_back(new TestObject(collider_manager_, GAME_WIDTH - 50, 240 + i * 64));
		game_objects_.push_back(new TestObject(collider_manager_, GAME_WIDTH - 50, 240 - i * 64));
	}*/
	
	/*for (int i = 0; i < 10; i++) {
		int x = rand() % (GAME_WIDTH-100) + 100;
		int y = rand() % (GAME_HEIGHT - 100) + 100;
		game_objects_.push_back(new TestObject(collider_manager_, (float)x, (float)y));
	}*/
	// -------------------------------------------------------------------------------------
	Scene::Initialize();
}
