#include "MainMenuScreen.h"
#include "constants.h"
#include "NotSoSuperMario.h"
#include "LevelOne.h"
#include "LevelSelect.h"
#include "LevelEditor.h"

MainMenu::MainMenu(Game* owner)
	:
	Scene(owner),
	mainMenuBg(Sprite("pictures\\mainmenubackground.png", 640, 480,1)),
	buttonbackground(Sprite("pictures\\buttonbackground.png", 320, 120,1)),
	mushicon(Sprite("pictures\\mushroombutton.png", 32, 32, 1))
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Initialize()
{
	mainMenuBg.Initialize(*graphics_);
	buttonbackground.Initialize(*graphics_);
	buttonbackground.GetImage().setX(GAME_WIDTH / 2.0f - buttonbackground.GetImage().getWidth() / 2.0f);
	buttonbackground.GetImage().setY(GAME_HEIGHT / 2.0f - buttonbackground.GetImage().getHeight() / 2.0f + 100.0f);

	mushicon.Initialize(*graphics_);
	mushicon.GetImage().setX(GAME_WIDTH / 2.0f - buttonbackground.GetImage().getWidth() / 2.0f + 40.0f);
	mushicon.GetImage().setY(GAME_HEIGHT / 2.0f - mushicon.GetImage().getHeight() / 2.0f + 80.0f);
	Scene::Initialize();
}

void MainMenu::Update(const float& frametime)
{
	Scene::Update(frametime);
	if (!is_down_) {
		if (input_->wasKeyPressed(SHIP_DOWN_KEY)) {
			mushicon.GetImage().setY(mushicon.GetImage().getY() + 20.0f);
			is_down_ = true;
		}
	}
	else if (is_down_) {
		if (input_->wasKeyPressed(SHIP_UP_KEY)) {
			mushicon.GetImage().setY(mushicon.GetImage().getY() - 20.0f);
			is_down_ = false;
		}
	}
	if (!is_down_) {
		if (input_->wasKeyPressed(VK_RETURN)) {
			dynamic_cast<NotSoSuperMario*>(owner_)->ChangeScene(new LevelSelect(owner_));
		}
	}
}

void MainMenu::ChildRender()
{
	mainMenuBg.Draw();
	buttonbackground.Draw();
	mushicon.Draw();
}
