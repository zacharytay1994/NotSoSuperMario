#include "Scene.h"
#include "GameObject.h"
#include "game.h"
#include <assert.h>

Scene::Scene(Game* owner)
	:
	owner_(owner)
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

	for each (GameObject * g in to_add_) {
		if (g != nullptr) {
			g->Initialize(*graphics_);
			game_objects_.push_back(g);
		}
	}
	to_add_.clear();
}

void Scene::AddObjectToScene(GameObject& object)
{
	to_add_.push_back(&object);
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
