#pragma once
#include "graphics.h"
#include "input.h"
#include "Sprite.h"
#include "Camera.h"
#include "Font.h"
#include <fstream>
#include <queue>
#include "input.h"

class Leaderboard {
private:
	Font* font_;
	Input* input_;
	Camera* camera_;
	Graphics* gfx_;

	Sprite toptensprite_;
	Sprite namesprite_;

	std::string filename_;

	Vec2<int> zerozero_;
	Vec2<int> placingpos_;
	Vec2<int> namepos_;
	Vec2<int> scorepos_;
	Vec2<int> playernamepos_;
	
	std::string placingTxt_ = "";
	std::string nameTxt_ = "";
	std::string scoreTxt_ = "";

	std::queue<std::string> nameQueue_ = std::queue<std::string>();
	std::queue<float> scoreQueue_ = std::queue<float>();

	float currentscore_ = -69696969.69f;
	std::string playername_ = "";

	bool currentIsTop10_ = false;
	bool hasName_ = false;

	bool isShowing_ = false;
	
public:
	Leaderboard(Graphics& gfx, Camera& camera, std::string filename);
	~Leaderboard();
	bool top10shown_ = false;
	void Initialize(Graphics& gfx, Input* input_);
	void Render();
	void Update(const float& frametime);

	void ReadLeaderboard();

	void InsertScore(float score);

	// insert player and generate text to display, also writes file
	void InsertPlayer(std::string name, float score);

	bool IsShowing();
};