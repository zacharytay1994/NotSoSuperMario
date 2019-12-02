#include "SaveMario.h"
#include "GameObject.h"

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
		save_file << (int)position_container_[i].x_ << "," << (int)position_container_[i].y_ << "\n";
	}
	save_file.close();
}

void SaveMario::AppendPositionToArray()
{
	if (recording_) {
		position_container_.push_back(Vec2<float>(mario_->GetPosition().x, mario_->GetPosition().y));
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
