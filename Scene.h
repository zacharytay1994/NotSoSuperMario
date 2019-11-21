#pragma once
#include "graphics.h"
#include "input.h"
#include <vector>

class GameObject;
class Scene {
private:
public:
	Graphics* graphics_;
	Input* input_;		
	std::vector<GameObject*> game_objects_;
	bool has_game_data_ = false;
public:
	Scene();
	~Scene();
	virtual void Update();
	void Render();
	virtual void ChildRender();
	void AddObjectToScene(GameObject& object);
	virtual void Initialize();
};