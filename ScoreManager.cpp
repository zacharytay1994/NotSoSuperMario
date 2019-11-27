#include "ScoreManager.h"

ScoreManager::ScoreManager(Graphics& gfx, Camera& camera)
	:
	gfx(&gfx),
	font_(new Font("pictures\\Fixedsys16x28.png", gfx, camera)),
	score_(0)
{ 
	
}

void ScoreManager::Draw()
{
	std::ostringstream ss;
	ss << "Score: " << score_;

	font_->DrawTextString(ss.str(), Vec2<int>(20, GAME_HEIGHT-50), *gfx);
}

void ScoreManager::IncrementScore() { score_++; }