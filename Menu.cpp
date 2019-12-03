#include "Menu.h"

Menu::Menu(Vec2<float> pos, Sprite background_) :
	menuPos(pos),
	background(background_)
{
}

Menu::~Menu()
{
	for each (Button* b in buttonList) {
		delete b;
		b = nullptr;
	}
}

void Menu::addButton(Button* b) {
	buttonList.push_back(b);
}

void Menu::SyncSpriteWithPos()
{
	background.GetImage().setX(menuPos.x_);
	background.GetImage().setY(menuPos.y_);
}

void Menu :: render() {
	background.Draw();
	for each (Button* b in buttonList) {
		
		b->SyncSpriteWithPos(menuPos);
		b->getSprite().Draw();
	}
}

Sprite& Menu::getSprite()
{
	return background;
}

void Menu::update(Input& i) {
	
	for each (Button* b in buttonList) {
		b->onClick(i);
	}
}


void Menu::MenuInitialise(Graphics& gfx) {
	background.Initialize(gfx);
	background.GetImage().setScale(CAMERA_ZOOM);
	for each (Button* b in buttonList) {
		b->ButtonInitialise(gfx);
	}
}