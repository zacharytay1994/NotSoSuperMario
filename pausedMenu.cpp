#include "pausedMenu.h"
#include "Camera.h"

pausedMenu::pausedMenu(Camera* camera)
	:
	pausedMenuBG(Sprite("pictures\\pausedMenuBg.png", 500, 250, 1)),
	mushIcon(Sprite("pictures\\mushroombutton.png", 32, 32, 1)),
	menuShowed(false),
	camera_(camera)
{

}

pausedMenu::~pausedMenu()
{
}

void pausedMenu::Initialize(Graphics& gfx)
{
	pausedMenuBG.Initialize(gfx);
}

void pausedMenu::Update(const float & frametime)
{
}

void pausedMenu::ChildRender()
{
	pausedMenuBG.Draw();
}

void pausedMenu::showMenu()
{
	//pausedMenuBG.Initialize(*graphics_);

	pausedMenuBG.GetImage().setX((640 / 2- pausedMenuBG.GetImage().getWidth()/ 2.0f) - camera_->GetCameraTransform().x_);
	pausedMenuBG.GetImage().setY((480/ 2- pausedMenuBG.GetImage().getHeight() / 2.0f ) - camera_->GetCameraTransform().y_);
	menuShowed = true;
}

bool pausedMenu::isMenuShowed()
{
	if (menuShowed = NULL) { return false; }
	else { return menuShowed; }
}