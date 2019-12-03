#pragma once

#include "Sprite.h"
#include "Button.h"
#include <vector>

class Menu {

private:
	std::string path;
	std::vector<Button*> buttonList;
	Vec2<float> menuPos = { 0.0f, 1.0f };
	Sprite background;
	
public:
	Menu(Vec2<float> pos, Sprite background);
	~Menu();
	void addButton(Button *b);
	void SyncSpriteWithPos();
	void update(Input& i);
	void render();
	void MenuInitialise(Graphics& gfx);
	Sprite& getSprite();

};


/*
- VECTOR of BUTTONS
- POSITION ON SCREEN (Vec2 float)

- Update { onclick()}
- Render 
*/