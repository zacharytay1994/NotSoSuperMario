#pragma once

#include "Sprite.h"
#include "Vec2.h"
#include "input.h"

class Button {
private:
	int height = 50;
	int width = 50;
	int buttonYPos;
	int buttonXPos;
	std::string path;
	Sprite buttonSprite;
	Vec2<float> relativePos = { 0.0f, 1.0f };


public:
	
	void SyncSpriteWithPos(Vec2<float> &menuPos);
	Button(Vec2<float> pos, Sprite buttonSprite);
	void render();
	bool onClick(Input& i);
	void ButtonInitialise(Graphics& gfx);
	Sprite& getSprite();
}
/*
BUTTON HAVE RELATIVE POSITION TO MENU (VEC2FLOAT)

OnClick function
*/;