#include "Scene.h"
#include "GameObject.h"
#include <assert.h>

Scene::Scene()
{
}

Scene::~Scene()
{
	for each (GameObject* g in game_objects_)
	{
		g = nullptr;
		delete g;
	}
}

void Scene::Update()
{
	for each (GameObject* g in game_objects_) {
		if (g != nullptr) {
			g->Update();
		}
	}
}

void Scene::AddObjectToScene(GameObject& object)
{
}

void Scene::Initialize()
{
	assert(has_game_data_);
	for each (GameObject * g in game_objects_) {
		g->Initialize(*graphics_);
	}
}

void Scene::Render()
{
	graphics_->spriteBegin();
	for each (GameObject* g in game_objects_) {
		if (g != nullptr) {
			g->Render();
		}
	}
	ChildRender();
	graphics_->spriteEnd();
}

void Scene::ChildRender()
{
}
