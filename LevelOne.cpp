#include "LevelOne.h"
#include "Mario.h"

LevelOne::LevelOne()
{
}

LevelOne::~LevelOne()
{
	graphics_ = nullptr;
	input_ = nullptr;
	delete graphics_;
	delete input_;
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
	Mario* temp = new Mario(*input_);
	game_objects_.push_back(temp);
	// -------------------------------------------------------------------------------------
	Scene::Initialize();
}
