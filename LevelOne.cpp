#include "LevelOne.h"
#include "Mario.h"
#include "TestObject.h"

LevelOne::LevelOne()
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
	Scene::Update(frametime);
}

void LevelOne::ChildRender()
{
	// by default render on Scene.h is called every frame which will render the gameobjects
}

void LevelOne::Initialize()
{
	// Place to initialize and add objects to scene ----------------------------------------
	game_objects_.push_back(new Mario(*input_, collider_manager_));
	game_objects_.push_back(new TestObject(collider_manager_, 320, GAME_HEIGHT - 50));
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
	}
	
	/*for (int i = 0; i < 10; i++) {
		int x = rand() % (GAME_WIDTH-100) + 100;
		int y = rand() % (GAME_HEIGHT - 100) + 100;
		game_objects_.push_back(new TestObject(collider_manager_, (float)x, (float)y));
	}*/
	// -------------------------------------------------------------------------------------
	Scene::Initialize();
}
