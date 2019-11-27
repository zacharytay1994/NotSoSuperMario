#pragma once
#include "game.h"

class Scene;
class NotSoSuperMario : public Game {
private:
	Scene* current_scene_;
public:
	NotSoSuperMario();
	~NotSoSuperMario();
	void update() override;
	void render() override;
	void collisions() override;
	void ai() override;
	void initialize(HWND hwnd);

	void ChangeScene(Scene* scene);
	void BindGameDataToScene();
};