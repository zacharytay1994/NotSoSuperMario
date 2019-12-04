#pragma once 
#include "GameObject.h"
#include "constants.h"
#include "Scene.h"
#include "Sprite.h"

class Camera;
class pausedMenu
{
private:
	Sprite pausedMenuBG;
	Sprite mushIcon;
	bool menuShowed;
	Camera* camera_;

public:
	pausedMenu(Camera* camera);
	~pausedMenu();
	void Initialize(Graphics& gfx);
	void showMenu();
	void Update(const float& frametime);
	void ChildRender();
	bool isMenuShowed();

};