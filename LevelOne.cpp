#include "LevelOne.h"
#include "GameObject.h"

LevelOne::LevelOne()
{
	// adding a GameObject into scene gameobject list for testing
	GameObject* temp = new GameObject(SHIP_IMAGE, SHIP_WIDTH, SHIP_HEIGHT, SHIP_COLS, D3DXVECTOR2(GAME_WIDTH/4, GAME_HEIGHT/4));
	game_objects_.push_back(temp);
}

LevelOne::~LevelOne()
{
	graphics_ = nullptr;
	input_ = nullptr;
	delete graphics_;
	delete input_;
}

void LevelOne::Update()
{
	Scene::Update();
}

void LevelOne::ChildRender()
{
	// by default render on Scene.h is called every frame which will render the gameobjects
}

void LevelOne::Initialize()
{
	Scene::Initialize();
}
