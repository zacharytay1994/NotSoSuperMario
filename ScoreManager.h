#pragma once

#include "Component.h"
#include "constants.h"
#include "graphics.h"
#include "Font.h"
#include <sstream>

class ScoreManager
{
	
private:
	Graphics* gfx;
	Font* font_;
	int score_;
public:
	ScoreManager(Graphics& gfx, Camera& camera);
	void Draw();
	void IncrementScore();
};