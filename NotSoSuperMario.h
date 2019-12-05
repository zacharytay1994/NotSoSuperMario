#pragma once
#include "game.h"

class Scene;
class NotSoSuperMario : public Game {
private:
	Scene* current_scene_;
	bool has_scene_ = false;
public:
	NotSoSuperMario();
	~NotSoSuperMario();
	void update() override;
	void render() override;
	void collisions() override;
	void ai() override;
	void initialize(HWND hwnd);

	void ChangeScene(Scene* scene);
	void ChangeSceneNonDelete(Scene* scene);
	void BindGameDataToScene();
};