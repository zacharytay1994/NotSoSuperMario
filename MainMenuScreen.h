#pragma once

#include "Scene.h"
#include "Sprite.h"
#include "GameObject.h"

class MainMenu : public Scene {
private:
	Sprite mainMenuBg;
	Sprite buttonbackground;
	Sprite mushicon;
	bool is_down_ = false;
public:
	MainMenu(Game* owner);
	~MainMenu();
	void Initialize() override;
	void Update(const float& frametime);
	void ChildRender();
};