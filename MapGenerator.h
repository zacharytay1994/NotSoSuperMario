#pragma once
#include <string>
#include <fstream>
#include <vector>

class ColliderManager;
class GameObject;
class MapGenerator {
private:
	std::string map_path_;
public:
	MapGenerator(const std::string& path);
	~MapGenerator();
	void GenerateWalls(ColliderManager& cm, std::vector<GameObject*>& golist);
};