#include "leaderboard.h"
#include <sstream>

Leaderboard::Leaderboard(Graphics& gfx, Camera& camera, std::string filename)
	:
	toptensprite_(Sprite("pictures\\leaderboard-bg.png",832,640,1)),
	namesprite_(Sprite("pictures\\leaderboard-bg-name.png",832,640,1)),
	camera_(&camera),
	font_(new Font("pictures\\Fixedsys16x28.png", gfx, camera, 0.75)),
	
	filename_("Leaderboard" + filename.substr(6, filename.length()-10) + "-leaderboard.txt")
{
}

Leaderboard::~Leaderboard()
{
}

void Leaderboard::Initialize(Graphics& gfx, Input* input)
{
	input_ = input;
	toptensprite_.Initialize(gfx);
	toptensprite_.GetImage().setScale(CAMERA_ZOOM);

	namesprite_.Initialize(gfx);
	namesprite_.GetImage().setScale(CAMERA_ZOOM);

	// top left position of toptensprite_ relative to camera
	zerozero_ = Vec2<int>(
		GAME_WIDTH / 2 - toptensprite_.GetWidth() / 2,
		GAME_HEIGHT / 2 - toptensprite_.GetHeight() / 2);
	placingpos_ = Vec2<int>(
		zerozero_.x_ + toptensprite_.GetWidth()/12*1.5,
		zerozero_.y_ + toptensprite_.GetWidth()/8);
	namepos_ = Vec2<int>(
		zerozero_.x_ + toptensprite_.GetWidth()/12*3,
		zerozero_.y_ + toptensprite_.GetWidth()/8);
	scorepos_ = Vec2<int>(
		zerozero_.x_ + toptensprite_.GetWidth()/12*8,
		zerozero_.y_ + toptensprite_.GetWidth()/8);
	playernamepos_ = Vec2<int>(
		zerozero_.x_ + namesprite_.GetWidth()/6,
		zerozero_.y_ + namesprite_.GetHeight()/4*3
		);
}

void Leaderboard::Render()
{
	if ((currentIsTop10_ && hasName_) || !currentIsTop10_) {
		toptensprite_.Draw();
		font_->DrawTextString(placingTxt_, placingpos_, *gfx_);
		font_->DrawTextString(nameTxt_, namepos_, *gfx_);
		font_->DrawTextString(scoreTxt_, scorepos_, *gfx_);
	}
	else{
		namesprite_.Draw();
		font_->DrawTextString(playername_, playernamepos_, *gfx_);
	}
}

void Leaderboard::Update(const float& frametime)
{
	if ((currentIsTop10_ && hasName_) || !currentIsTop10_) {
		toptensprite_.SetX(zerozero_.x_ - camera_->GetCameraTransform().x_);
		toptensprite_.SetY(zerozero_.y_ - camera_->GetCameraTransform().y_);
	}
	else {
		namesprite_.SetX(zerozero_.x_ - camera_->GetCameraTransform().x_);
		namesprite_.SetY(zerozero_.y_ - camera_->GetCameraTransform().y_);

		if (input_->wasKeyPressed(VK_RETURN) && playername_ != "") {
			hasName_ = true;
			InsertPlayer(playername_, currentscore_);
		}
		if (!hasName_)
			playername_ = input_->getTextIn();

	}
}

void Leaderboard::ReadLeaderboard()
{
	std::ifstream file(filename_);
	if (file.is_open()) {
		std::string line;
		std::string lastline;
		int commaindex = 0;
		while (std::getline(file, line)) {
			if (line.length() == 0) {
				break;
			}
			commaindex = line.find(",");
			nameQueue_.push(line.substr(0, commaindex));
			scoreQueue_.push(std::stof(line.substr(commaindex + 1, line.length())));
			lastline = line;
		}
		if (line.length() > 0) {
			currentIsTop10_ =
				currentscore_ < std::stof(lastline.substr(commaindex + 1, lastline.length())) ||
				scoreQueue_.size() < 10;
		}
		else {
			currentIsTop10_ = true;
		}
		if (currentIsTop10_) {
			input_->clearTextIn();
		} else {
			InsertPlayer(playername_, currentscore_);
		}
		
	}
	file.close();
}

void Leaderboard::InsertPlayer(std::string name, float score) {

	std::ofstream savefile;

	savefile.open(filename_);

	

	bool inserted = false;
	for (int i = 1; i <= 10; i-=-1)
	{
		std::stringstream ss;

		if (!scoreQueue_.empty() || !inserted) {
			ss << i << "\n";
			placingTxt_ += ss.str();
		}

		ss.str("");
		ss.clear();
		ss.precision(3);
		ss << std::fixed;

		if (scoreQueue_.empty()) {
			if (!inserted) {
				ss << score << "\n";
				scoreTxt_ += ss.str();
				nameTxt_ += name + "\n";
				savefile << name + "," + ss.str();
				inserted = true;
			}
			break;
		}

		if (score < scoreQueue_.front() && !inserted) {
			ss << score << "\n";
			scoreTxt_ += ss.str();
			nameTxt_ += name + "\n";
			savefile << name + "," + ss.str();
			inserted = true;
		} else {
			ss << scoreQueue_.front() << "\n";
			scoreTxt_ += ss.str();
			nameTxt_ += nameQueue_.front() + "\n";
			savefile << nameQueue_.front() + "," + ss.str();
			scoreQueue_.pop();
			nameQueue_.pop();
		}

	}
	savefile.close();
	top10shown_ = true;
}

void Leaderboard::InsertScore(float score) {
	currentscore_ = score;
	ReadLeaderboard();
}

bool Leaderboard::HasScore() {
	return currentscore_ != -431602080;
}
