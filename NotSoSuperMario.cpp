#include "NotSoSuperMario.h"
#include "LevelOne.h"
#include "MainMenuScreen.h"

NotSoSuperMario::NotSoSuperMario()
{
}

NotSoSuperMario::~NotSoSuperMario()
{
	delete current_scene_;
	current_scene_ = nullptr;
	Game::releaseAll();
}

void NotSoSuperMario::update()
{
	if (current_scene_ != nullptr) {
		current_scene_->Update(frameTime);
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
	ChangeScene(new MainMenu(this));
}

void NotSoSuperMario::ChangeScene(Scene* scene)
{
	if (has_scene_) {
		delete current_scene_;
	}
	current_scene_ = scene;
	BindGameDataToScene();
	current_scene_->Initialize();
}

void NotSoSuperMario::ChangeSceneNonDelete(Scene* scene)
{
	current_scene_ = scene;
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
