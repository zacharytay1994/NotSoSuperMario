#pragma once
#include "Vec2.h"
#include <string>
#include <fstream>
#include <vector>

class ScoreManager;
class ColliderManager;
class GameObject;
class Mario;
class Scene;
class MapGenerator {
private:
	std::string map_path_;
	Vec2<float> mario_position_ = Vec2<float>(0.0f,0.0f);
public:
	MapGenerator(const std::string& path);
	~MapGenerator();
	void GenerateWalls(ColliderManager& cm, std::vector<GameObject*>& golist, ScoreManager& sm, Scene& s, Mario& m);
	Vec2<float> GetMarioPosition();
};