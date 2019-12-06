#pragma once

#include "Scene.h"
#include "Sprite.h"
#include "GameObject.h"
#include "Background.h"
#include "Camera.h"
#include "Vec2.h"

class MainMenu : public Scene {
private:
	Sprite mainMenuBg;
	Sprite* button_to_render_;
	Sprite buttonbackground;
	Sprite buttonbackground2;
	Sprite buttonbackground3;
	Sprite buttonbackground4;
	Sprite mushicon;
	Sprite pseudogoomba_;
	Sprite pseudokoopa_;
	bool is_down_ = false;
	GameObject camera_drag_ = GameObject("pictures\\marioidle.png", 64, 64, 1, D3DXVECTOR2(GAME_WIDTH/2, GAME_HEIGHT/2));
	Background bg1;
	Background bg2;
	Background bg3;
	Background bg4;
	Background bg5;
	Camera cam_;
	Vec2<float> hover_position_ = Vec2<float>(GAME_WIDTH / 2, GAME_HEIGHT/2 - 100);
	float radians_ = 0.0f;
	float hover_strength_ = 100.0f;
	int index_ = 1;
	float walking_speed_ = -20.0f;
	float walking_speed_2_ = 20.0f;
	bool is_select_sound_played_ = false;
	bool is_sound_initialized = false;
public:
	MainMenu(Game* owner);
	~MainMenu();
	void Initialize() override;
	void Update(const float& frametime);
	void ChildRender();
	void UpdateHover(const float& frametime);
	void WalkStuff(const float& frametime);
};