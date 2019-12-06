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
	std::ostringstream ss1;


	ss << "Score: " << timer_->Duration() - score_;
	ss1 << " / " << score_to_beat_;
	total_score_ = timer_->Duration() - score_;

	font_->DrawTextString(ss.str(), Vec2<int>(10.0f, 10.0f), *gfx);
	font_->DrawTextString(ss1.str() + " -Restart (R)", Vec2<int>(300.0f, 10.0f), *gfx);
}

void ScoreManager::IncrementScore() { score_++; }

float ScoreManager::GetScore()
{
	return total_score_;
}

void ScoreManager::SetScoreToBeat(const float& score)
{
	score_to_beat_ = score;
}
