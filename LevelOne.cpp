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
	game_objects_.push_back(new TestObject(collider_manager_));
	// -------------------------------------------------------------------------------------
	Scene::Initialize();
}
