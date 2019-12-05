#include "ScoreManager.h"


ScoreManager::ScoreManager(Graphics& gfx, Camera& camera, Timer& timer)
	:
	gfx(&gfx),
	font_(new Font("pictures\\Fixedsys16x28.png", gfx, camera)),
	score_(0),
	timer_(&timer)
{ 
	
}

void ScoreManager::Draw()
{
	std::ostringstream ss;


	ss << "Score: " << timer_ ->Duration() - score_;

	font_->DrawTextString(ss.str(), Vec2<int>(20, GAME_HEIGHT-50), *gfx);
}

void ScoreManager::IncrementScore() { score_++; }
