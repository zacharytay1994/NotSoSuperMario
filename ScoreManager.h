#pragma once

#include "Component.h"
#include "constants.h"
#include "graphics.h"
#include "Font.h"
#include <sstream>
#include "Timer.h"
class ScoreManager
{
	
private:
	Graphics* gfx;
	Font* font_;
	Timer* timer_;
	int score_;


public:
	ScoreManager(Graphics& gfx, Camera& camera, Timer& timer);
	void Draw();
	void IncrementScore();

};