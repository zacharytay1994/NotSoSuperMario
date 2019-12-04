#include "pausedMenu.h"
#include "Camera.h"
#include <string>

pausedMenu::pausedMenu(Camera* camera)
	:
	pausedMenuBG(Sprite("pictures\\pausedMenuBg.png", 500, 250, 1)),
	mushIcon(Sprite("pictures\\mushroombutton.png", 32, 32, 1)),
	menuShowed(false),
	camera_(camera),
	input_(new Input())

{

}

pausedMenu::~pausedMenu()
{
}

void pausedMenu::Initialize(Graphics& gfx, Input* input)
{
	input_ = input;
	pausedMenuBG.Initialize(gfx);
	mushIcon.Initialize(gfx);
}

void pausedMenu::Update(const float & frametime)
{
	if (y_offset != 100)
	{
		if (input_->wasKeyPressed(VK_DOWN))
		{
			y_offset += 50;
		}
	}

	if (y_offset != 0)
	{
		if (input_->wasKeyPressed(VK_UP))
		{
			y_offset -= 50;
		}
	}

	//check selection
	if (y_offset == 0)
	{
		selection = 0;
	}
	if (y_offset == 50)
	{
		selection = 1;
	}
	if (y_offset == 100)
	{
		selection = 2;
	}
	 
}

void pausedMenu::ChildRender()
{
	pausedMenuBG.Draw();
	mushIcon.Draw();
	menuShowed = true;
}

void pausedMenu::showMenu()
{

	float x = (640 / 2 - pausedMenuBG.GetImage().getWidth() / 2.0f) - camera_->GetCameraTransform().x_;
	float y = (480 / 2 - pausedMenuBG.GetImage().getHeight() / 2.0f) - camera_->GetCameraTransform().y_;

	pausedMenuBG.GetImage().setX(x);
	pausedMenuBG.GetImage().setY(y);

	mushIcon.GetImage().setX(x + 50.0f );
	mushIcon.GetImage().setY(y + 44.0f + y_offset);
	
}

int pausedMenu::selectionValue()
{
	return selection;
}