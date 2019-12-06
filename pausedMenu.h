#pragma once 
#include "GameObject.h"
#include "constants.h"
#include "Scene.h"
#include "Sprite.h"
#include "input.h"

class Camera;
class pausedMenu
{
private:
	Sprite pausedMenuBG;
	Sprite pausedMenuBGForTesting;
	Sprite mushIcon;
	bool menuShowed;
	Camera* camera_;
	Input* input_;
	float y_offset = 0;
	int selection = 0;
public:
	pausedMenu(Camera* camera);
	~pausedMenu();
	void Initialize(Graphics& gfx, Input* input_);
	void showMenu();
	void Update(const float& frametime);
	void ChildRender(bool is_testing_ = false);
	int selectionValue();

};