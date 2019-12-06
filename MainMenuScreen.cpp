#include "MainMenuScreen.h"
#include "constants.h"
#include "NotSoSuperMario.h"
#include "LevelOne.h"
#include "LevelSelect.h"
#include "LevelEditor.h"

#include <string>
#include <iostream>
#include <sstream>

MainMenu::MainMenu(Game* owner)
	:
	Scene(owner),
	mainMenuBg(Sprite("pictures\\mainmenubackground.png", 640, 480,1)),
	buttonbackground(Sprite("pictures\\buttonbackground.png", 320, 180,1)),
	buttonbackground2(Sprite("pictures\\buttonbackground2.png", 320, 180, 1)),
	buttonbackground3(Sprite("pictures\\buttonbackground3.png", 320, 180, 1)),
	buttonbackground4(Sprite("pictures\\buttonbackground4.png", 320, 180, 1)),
	mushicon(Sprite("pictures\\mushroombutton.png", 32, 32, 1)),
	bg1("pictures\\menutitle.png", 664, 448, 1, cam_, 0.2f, 0.1f, 0.0f, 0.0f, 1, 1),
	bg2("pictures\\mountainbackground.png", 1200, 1200, 1, cam_, 0.5f, 0.20f, -300.0f, -760.0f * CAMERA_ZOOM, 10, 1),
	bg3("pictures\\cloudbackground.png", 1200, 1200, 1, cam_, 0.4f, 0.15f, -300.0f, -460.0f * CAMERA_ZOOM, 10, 1),
	bg4("pictures\\rockbackground.png", 1200, 1200, 1, cam_, 0.3f, 0.10f, -300.0f, -360.0f * CAMERA_ZOOM, 10, 1),
	bg5("pictures\\bushesbackground.png", 1200, 700, 1, cam_, 0.2f, 0.05f, -300.0f, 400.0f * CAMERA_ZOOM, 10, 1),
	pseudogoomba_(Sprite("pictures\\goombawalksheet.png", 64, 64, 4)),
	pseudokoopa_(Sprite("pictures\\kooparunsheet.png", 64, 64, 8))
{
	button_to_render_ = &buttonbackground;
}

MainMenu::~MainMenu()
{
}

void MainMenu::Initialize()
{
	mainMenuBg.Initialize(*graphics_);
	buttonbackground.Initialize(*graphics_);
	buttonbackground2.Initialize(*graphics_);
	buttonbackground3.Initialize(*graphics_);
	buttonbackground4.Initialize(*graphics_);
	buttonbackground.GetImage().setX(GAME_WIDTH / 2.0f - buttonbackground.GetImage().getWidth() / 2.0f);
	buttonbackground.GetImage().setY(GAME_HEIGHT / 2.0f - buttonbackground.GetImage().getHeight() / 2.0f + 100.0f);
	buttonbackground2.GetImage().setX(GAME_WIDTH / 2.0f - buttonbackground.GetImage().getWidth() / 2.0f);
	buttonbackground2.GetImage().setY(GAME_HEIGHT / 2.0f - buttonbackground.GetImage().getHeight() / 2.0f + 100.0f);
	buttonbackground3.GetImage().setX(GAME_WIDTH / 2.0f - buttonbackground.GetImage().getWidth() / 2.0f);
	buttonbackground3.GetImage().setY(GAME_HEIGHT / 2.0f - buttonbackground.GetImage().getHeight() / 2.0f + 100.0f);
	buttonbackground4.GetImage().setX(GAME_WIDTH / 2.0f - buttonbackground.GetImage().getWidth() / 2.0f);
	buttonbackground4.GetImage().setY(GAME_HEIGHT / 2.0f - buttonbackground.GetImage().getHeight() / 2.0f + 100.0f);

	mushicon.Initialize(*graphics_);
	mushicon.GetImage().setX(GAME_WIDTH / 2.0f - buttonbackground.GetImage().getWidth() / 2.0f + 40.0f);
	mushicon.GetImage().setY(GAME_HEIGHT / 2.0f - mushicon.GetImage().getHeight() / 2.0f + 50.0f);

	bg1.Initialize(*graphics_);
	bg1.ForceUpdate(false);
	bg1.SetPosition(GAME_WIDTH / 2 * CAMERA_ZOOM, GAME_HEIGHT / 2 * CAMERA_ZOOM - 100);
	bg2.Initialize(*graphics_);
	bg3.Initialize(*graphics_);
	bg4.Initialize(*graphics_);
	bg5.Initialize(*graphics_);
	bg2.SetScrollRate(5.0f);
	bg3.SetScrollRate(10.0f);
	bg4.SetScrollRate(15.0f);
	camera_drag_.Initialize(*graphics_);
	cam_.SetTarget(&camera_drag_);
	cam_.SetCameraBounds(-100, -1000.0f, 1000.0f, 1000.0f);
	bg1.SetLerpStrength(0.2f);

	// init mob sprite
	pseudogoomba_.Initialize(*graphics_);
	pseudogoomba_.InitializeAnimation(0, 5, 0.25);
	pseudogoomba_.GetImage().setX(GAME_WIDTH / 2);
	pseudogoomba_.GetImage().setY(GAME_HEIGHT - 104);
	pseudokoopa_.Initialize(*graphics_);
	pseudokoopa_.InitializeAnimation(0, 7, 0.25);
	pseudokoopa_.GetImage().setX(GAME_WIDTH / 2);
	pseudokoopa_.GetImage().setY(GAME_HEIGHT - 104);
	pseudokoopa_.GetImage().flipHorizontal(true);
	Scene::Initialize();

	if (!is_sound_initialized)
	{
		PlaySound("sounds\\smb_coin.wav", NULL, SND_FILENAME || SND_ASYNC);
		PlaySound("sounds\\smb_jump-super.wav", NULL, SND_FILENAME || SND_ASYNC);
		PlaySound("sounds\smb_mariodie.wav", NULL, SND_FILENAME || SND_ASYNC);
		PlaySound("sounds\\smb_powerup.wav", NULL, SND_FILENAME || SND_ASYNC);
		is_sound_initialized = true;
	}
}

void MainMenu::Update(const float& frametime)
{
	Scene::Update(frametime);
	if (index_ <= 3) {
		if (input_->wasKeyPressed(SHIP_DOWN_KEY)) {
			is_select_sound_played_ = false;
			if (!is_select_sound_played_)
			{
				PlaySound("sounds\\smb_coin.wav", NULL, SND_FILENAME || SND_ASYNC);
				is_select_sound_played_ = true;
			}
			mushicon.GetImage().setY(mushicon.GetImage().getY() + 32.0f);
			//is_down_ = true;
			index_++;
		}
	}
	if (index_ >= 2) {
		is_select_sound_played_ = false;
		if (input_->wasKeyPressed(SHIP_UP_KEY)) {
			PlaySound("sounds\\smb_coin.wav", NULL, SND_FILENAME || SND_ASYNC);
			mushicon.GetImage().setY(mushicon.GetImage().getY() - 32.0f);
			//is_down_ = false;
			index_--;
		}
	}
	switch (index_) {
	case 1:
		button_to_render_ = &buttonbackground;
		if (input_->wasKeyPressed(VK_RETURN)) {
			dynamic_cast<NotSoSuperMario*>(owner_)->ChangeScene(new LevelSelect(owner_));
		}
		break;
	case 2:
		button_to_render_ = &buttonbackground2;
		if (input_->wasKeyPressed(VK_RETURN)) {
			dynamic_cast<NotSoSuperMario*>(owner_)->ChangeScene(new LevelEditor(owner_)/*new LevelOne(owner_, "Levels/levelone.txt")*/);
		}
		break;
	case 3:
		button_to_render_ = &buttonbackground3;
		//if (input_->wasKeyPressed(VK_RETURN)) {
		//	dynamic_cast<NotSoSuperMario*>(owner_)->ChangeScene(new LevelSelect(owner_)/*new LevelOne(owner_, "Levels/levelone.txt")*/);
		//}
		break;
	case 4:
		button_to_render_ = &buttonbackground4;
		//owner_->PostQuitMessage(0);
		break;
	}

	// effects
	camera_drag_.Update(frametime);
	cam_.Update(frametime);
	bg1.Update(frametime);
	bg1.LerpToPosition(frametime);
	bg2.Update(frametime);
	bg3.Update(frametime);
	bg4.Update(frametime);
	bg5.Update(frametime);
	bg2.ScrollBackground(frametime);
	bg3.ScrollBackground(frametime);
	bg4.ScrollBackground(frametime);
	bg5.ScrollBackground(frametime);
	UpdateHover(frametime);
	camera_drag_.SetPosition(hover_position_.x_ + 32, hover_position_.y_);
	pseudogoomba_.Update(frametime);
	pseudokoopa_.Update(frametime);
	WalkStuff(frametime);
}

void MainMenu::ChildRender()
{
	bg2.Draw();
	bg3.Draw();
	bg4.Draw();
	bg5.Draw();
	mainMenuBg.Draw();
	button_to_render_->Draw();
	mushicon.Draw();
	bg1.Draw();
	pseudogoomba_.Draw();
	pseudokoopa_.Draw();
}

void MainMenu::UpdateHover(const float& frametime)
{
	if (radians_ < 6.284f) {
		radians_ += 1.0f * frametime;
	}
	else {
		radians_ = 0.0f;
	}
	/*std::stringstream ss;
	ss << std::sin(radians_) << std::endl;
	OutputDebugString(ss.str().c_str());*/
	hover_position_.y_ = (GAME_HEIGHT/2 - 100) + std::sin(radians_) * hover_strength_;
}

void MainMenu::WalkStuff(const float& frametime)
{
	if (pseudogoomba_.GetImage().getX() < 0.0f) {
		pseudogoomba_.GetImage().flipHorizontal(true);
		walking_speed_ *= -1;
	}
	else if (pseudogoomba_.GetImage().getX() > GAME_WIDTH - pseudogoomba_.GetImage().getWidth()) {
		pseudogoomba_.GetImage().flipHorizontal(false);
		walking_speed_ *= -1;
	}
	if (pseudokoopa_.GetImage().getX() < 0.0f) {
		pseudokoopa_.GetImage().flipHorizontal(true);
		walking_speed_2_ *= -1;
	}
	else if (pseudokoopa_.GetImage().getX() > GAME_WIDTH - pseudokoopa_.GetImage().getWidth()) {
		pseudokoopa_.GetImage().flipHorizontal(false);
		walking_speed_2_ *= -1;
	}
	pseudogoomba_.GetImage().setX(pseudogoomba_.GetImage().getX() + walking_speed_ * frametime);
	pseudokoopa_.GetImage().setX(pseudokoopa_.GetImage().getX() + walking_speed_2_ * frametime);
}
