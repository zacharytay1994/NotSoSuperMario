#include "NotSoSuperMario.h"
#include "LevelOne.h"

NotSoSuperMario::NotSoSuperMario()
{
}

NotSoSuperMario::~NotSoSuperMario()
{
	current_scene_ = nullptr;
	delete current_scene_;
	Game::releaseAll();
}

void NotSoSuperMario::update()
{
	if (current_scene_ != nullptr) {
		current_scene_->Update();
	}
}

void NotSoSuperMario::render()
{
	if (current_scene_ != nullptr) {
		current_scene_->Render();
	}
}

void NotSoSuperMario::collisions()
{
}

void NotSoSuperMario::ai()
{
}

void NotSoSuperMario::initialize(HWND hwnd)
{
	Game::initialize(hwnd);
	ChangeScene(*(new LevelOne()));
}

void NotSoSuperMario::ChangeScene(Scene& scene)
{
	current_scene_ = &scene;
	BindGameDataToScene();
	current_scene_->Initialize();
}

void NotSoSuperMario::BindGameDataToScene()
{
	if (current_scene_ != nullptr) {
		current_scene_->graphics_ = graphics;
		current_scene_->input_ = input;
		current_scene_->has_game_data_ = true;
	}
}
