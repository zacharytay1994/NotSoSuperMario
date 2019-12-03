
#include "Button.h"
#include <string>
#include <sstream>


Button::Button(Vec2<float> pos, Sprite buttonSprite) :
	relativePos(pos),
	buttonSprite(buttonSprite)
{
}

void Button::ButtonInitialise(Graphics& gfx) {
	buttonSprite.Initialize(gfx);
	buttonSprite.GetImage().setScale(CAMERA_ZOOM);
}

void Button::SyncSpriteWithPos(Vec2<float> &menuPos)
{
	buttonYPos = relativePos.y_ + menuPos.y_;
	buttonXPos = relativePos.x_ + menuPos.x_;
	buttonSprite.GetImage().setX((buttonYPos));
	buttonSprite.GetImage().setY((buttonXPos));
}

Sprite& Button::getSprite() {
	return buttonSprite;
}

bool Button::onClick(Input& i) {
	
	
	int mouseY= i.getMouseY();
	int mouseX = i.getMouseX();
	
	int left = buttonXPos - width;
	int right = buttonXPos + width;
	int up = buttonYPos + height;
	int down = buttonXPos - height;
	bool isInside = ((mouseX >= left && right <= mouseX) && (mouseY >= up && down <= mouseY));

	std::stringstream test;
	test << "X:" << mouseX << std::endl;
	test << "Y:" << mouseY << std::endl;
	test << "Left:" << left << std::endl;
	test << "Right:" << right << std::endl;
	test << "Up:" << up << std::endl;
	test << "Down:" << down << std::endl;
	test << "MOUSE INSIDE:" << isInside << std::endl;
	OutputDebugString(test.str().c_str());


	if (mouseX >= left && right >= mouseX)
	{
		if (mouseY>= up && down >= mouseY) {
			exit;
			return true;
		}
	}
	return false;
}
