#pragma once
#include "Vec2.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class GameObject;
class LoadMario {
private:
	std::string file_name_;
	GameObject* mario_;
	float record_rate_ = 0.001f;
	float record_timer_ = 0.0f;
	int position_index_ = 0;
	int positions_length_ = 0;
	std::vector<Vec2<float>> positions_;
	std::vector<Vec2<int>> sprite_animation_;
	std::vector<int> sprite_flip_;
	bool loaded_ = false;
public:
	LoadMario(const std::string& file);
	~LoadMario();
	void BindMario(GameObject* mario);
	void ExecuteMovement(const float& frametime);
	void Update(const float& frametime);
	void ReadPositions();
};