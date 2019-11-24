#include "MapGenerator.h"
#include "TestObject.h"

MapGenerator::MapGenerator(const std::string& path)
	:
	map_path_(path)
{
}

MapGenerator::~MapGenerator()
{
}

void MapGenerator::GenerateWalls(ColliderManager& cm, std::vector<GameObject*>& golist)
{
	int start_x = 0;
	int start_y = 0;
	int cell_size_ = 62 * CAMERA_ZOOM;
	std::ifstream file(map_path_);
	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			for each (char c in line) {
				if (c == 'x') {
					golist.push_back(new TestObject(cm, start_x * cell_size_, start_y * cell_size_));
				}
				start_x++;
			}
			start_x = 0;
			start_y++;
		}
	}
}
