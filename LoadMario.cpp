#include "LoadMario.h"
#include "GameObject.h"

LoadMario::LoadMario(const std::string& file)
	:
	file_name_(file)
{
	ReadPositions();
	positions_length_ = positions_.size();
}

LoadMario::~LoadMario()
{
}

void LoadMario::BindMario(GameObject* mario)
{
	mario_ = mario;
	loaded_ = true;
}

void LoadMario::ExecuteMovement(const float& frametime)
{
	if (mario_ != nullptr) {
		if (record_timer_ < record_rate_) {
			record_timer_ += frametime;
		}
		else {
			if (position_index_ < positions_length_ - 1) {
				record_timer_ = 0.0f;
				mario_->SetPosition(positions_[position_index_].x_, positions_[position_index_].y_);
				position_index_++;
			}
		}
	}
}

void LoadMario::Update(const float& frametime)
{
	if (loaded_) {
		ExecuteMovement(frametime);
	}
}

void LoadMario::ReadPositions()
{
	std::ifstream save_file(file_name_);
	if (save_file.is_open()) {
		std::string line;
		while (std::getline(save_file, line)) {
			const int comma_pos = line.find(",");
			int x = std::stoi(line.substr(0, comma_pos));
			int y = std::stoi(line.substr(comma_pos + 1, line.length() - 1));
			positions_.push_back(Vec2<float>((float)x, (float)y));
		}
	}

}

