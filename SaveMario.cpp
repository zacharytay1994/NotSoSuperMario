#include "SaveMario.h"
#include "GameObject.h"
#include "Mario.h"
#include "Vec2.h"

SaveMario::SaveMario(const std::string& savefile)
	:
	file_name_(savefile)
{
}

SaveMario::~SaveMario()
{
	WritePositionToFile();
}

void SaveMario::WritePositionToFile()
{
	std::ofstream save_file;
	
	save_file.open(file_name_);
	for (int i = 0; i < position_container_.size(); i++) {
		save_file << (int)position_container_[i].x_ << "," << (int)position_container_[i].y_ << "s" <<
			sprite_data_container_[i].x_  << "," << sprite_data_container_[i].y_ << "f" <<
			sprite_flipped_[i] <<
			"\n";
	}
	save_file.close();
}

void SaveMario::AppendPositionToArray()
{
	if (recording_) {
		position_container_.push_back(Vec2<float>(mario_->GetPosition().x, mario_->GetPosition().y));
		Mario* temp = dynamic_cast<Mario*>(mario_);
		sprite_data_container_.push_back(Vec2<int>(temp->animation_id_, temp->sprite_->GetImage().getCurrentFrame()));
		sprite_flipped_.push_back(temp->sprite_->GetImage().GetFlipHorizontal());
	}
}

void SaveMario::Update(const float& frametime)
{
	if (record_timer_ < record_rate_) {
		record_timer_ += frametime;
	}
	else {
		record_timer_ = 0.0f;
		AppendPositionToArray();
	}
}

void SaveMario::BindMario(GameObject* mario)
{
	mario_ = mario;
}

void SaveMario::StartRecording(const bool& record)
{
	recording_ = record;
}
