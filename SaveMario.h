#pragma once

#include "Vec2.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class GameObject;
class SaveMario {
private:
	std::string file_name_;
	bool recording_;
	std::vector<Vec2<float>> position_container_;
	GameObject* mario_;
	
	float record_rate_ = 0.005f;
	float record_timer_ = 0.0f;
public:
	SaveMario(const std::string& savefile);
	~SaveMario();
	void WritePositionToFile();
	void AppendPositionToArray();
	void Update(const float& frametime);
	void BindMario(GameObject* mario);
	void StartRecording(const bool& record);
};