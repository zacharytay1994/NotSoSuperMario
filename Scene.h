#pragma once
#include "graphics.h"
#include "input.h"
#include <vector>

class Game;
class GameObject;
class Scene {
private:
public:
	Game* owner_;
	Graphics* graphics_;
	Input* input_;		
	std::vector<GameObject*> game_objects_;
	std::vector<GameObject*> to_add_;
	bool has_game_data_ = false;
public:
	Scene(Game* owner);
	virtual ~Scene();
	virtual void Update(const float& frametime);
	void Render();
	virtual void ChildRender();
	virtual void BackgroundRender();
	void AddObjectToScene(GameObject& object);
	virtual void Initialize();
};