#pragma once
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
public:
	MapGenerator(const std::string& path);
	~MapGenerator();
	void GenerateWalls(ColliderManager& cm, std::vector<GameObject*>& golist, ScoreManager& sm, Scene& s, Mario& m);
};