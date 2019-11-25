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

void Scene::Update(const float& frametime)
{
	for each (GameObject* g in game_objects_) {
		if (g != nullptr) {
			if (!g->removed_) {
				g->Update(frametime);
			}
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
	BackgroundRender();
	for each (GameObject* g in game_objects_) {
		if (g != nullptr) {
			if (!g->removed_) {
				g->Render();
			}
		}
	}
	ChildRender();
	graphics_->spriteEnd();
}

void Scene::ChildRender()
{
}

void Scene::BackgroundRender()
{
}
