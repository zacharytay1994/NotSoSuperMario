#include "LoadMario.h"
#include "GameObject.h"
#include "MarioGhost.h"

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
		MarioGhost* casted_mario = dynamic_cast<MarioGhost*>(mario_);
		if (record_timer_ < record_rate_) {
			record_timer_ += frametime;
		}
		else {
			if (position_index_ < positions_length_ - 1) {
				// update position
				record_timer_ = 0.0f;
				mario_->SetPosition(positions_[position_index_].x_, positions_[position_index_].y_);
				// update sprite
				switch (sprite_animation_[position_index_].x_) {
					case 0:
						casted_mario->ChangeSprite(casted_mario->hold_);
						break;
					case 1:
						casted_mario->ChangeSprite(casted_mario->running_animation_);
						break;
					case 2:
						casted_mario->ChangeSprite(casted_mario->jumping_animation_);
						break;
				}
				// update frame
				casted_mario->sprite_->GetImage().setCurrentFrame(sprite_animation_[position_index_].y_);
				// update flip
				if (sprite_flip_[position_index_] == 0) {
					casted_mario->sprite_->GetImage().flipHorizontal(false);
				}
				else {
					casted_mario->sprite_->GetImage().flipHorizontal(true);
				}
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
			// Get position 
			const int position_s = line.find("s");
			const int comma_pos = line.find(",");
			int x = std::stoi(line.substr(0, comma_pos));
			int y = std::stoi(line.substr(comma_pos + 1, position_s - comma_pos - 1));
			positions_.push_back(Vec2<float>((float)x, (float)y));
			// Get animation data
			const int position_f = line.find("f");
			const int comma_sprite_data = line.find(",", position_s);
			int animation_x = std::stoi(line.substr(position_s + 1, comma_sprite_data - position_s - 1));
			int animation_y = std::stoi(line.substr(comma_sprite_data + 1, position_f - comma_sprite_data - 1));
			sprite_animation_.push_back(Vec2<int>(animation_x, animation_y));
			// Get flip flag
			int animation_flip = std::stoi(line.substr(position_f + 1, 1));
			sprite_flip_.push_back(animation_flip);
		}
	}
}

