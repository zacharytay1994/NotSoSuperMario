#include "MapGenerator.h"
#include "TestObject.h"
#include "Coin.h"
#include "Goomba.h"
#include "QuestionMarkBlock.h"

MapGenerator::MapGenerator(const std::string& path)
	:
	map_path_(path)
{
}

MapGenerator::~MapGenerator()
{
}

void MapGenerator::GenerateWalls(ColliderManager& cm, std::vector<GameObject*>& golist, ScoreManager& sm, Scene& s, Mario& m)
{
	int start_x = 0;
	int start_y = 0;
	int cell_size_ = 64 * CAMERA_ZOOM;
	std::ifstream file(map_path_);
	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			for each (char c in line) {
				if (c == 'x') {
					golist.push_back(new TestObject(cm, start_x * cell_size_, start_y * cell_size_));
				}
				else if (c == 'c') {
					golist.push_back(new Coin(cm, Vec2<float>( start_x * cell_size_, start_y * cell_size_ ), &sm));
				}
				else if (c == 'g') {
					golist.push_back(new Goomba(cm, Vec2<float>(start_x * cell_size_, start_y * cell_size_)));
				}
				else if (c == 'q') {
					golist.push_back(new QuestionMarkBlock(cm, Vec2<float>(start_x * cell_size_, start_y * cell_size_), s, m));
				}
				start_x++;
			}
			start_x = 0;
			start_y++;
		}
	}
}
