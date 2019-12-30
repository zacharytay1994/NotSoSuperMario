#include "MarioGhost.h"

MarioGhost::MarioGhost()
	:
	GameObject("pictures\\" + theme + "\\marioghostidle.png", 64, 64, 1, D3DXVECTOR2(200 * CAMERA_ZOOM, 100 * CAMERA_ZOOM)),
	running_animation_(new Sprite("pictures\\" + theme + "\\marioghostrunsheet.png", 64, 64, 3)),
	jumping_animation_(new Sprite("pictures\\" + theme + "\\marioghostjumping.png", 64, 64, 3))
{
}

MarioGhost::~MarioGhost()
{
	delete running_animation_;
	running_animation_ = nullptr;
	delete jumping_animation_;
	jumping_animation_ = nullptr;
}

void MarioGhost::Update(const float& frametime)
{
	GameObject::Update(frametime);
}

void MarioGhost::Render()
{
	GameObject::Render();
}

void MarioGhost::ChildInitialize(Graphics& gfx)
{
	running_animation_->Initialize(gfx);
	running_animation_->GetImage().setScale(CAMERA_ZOOM);
	jumping_animation_->Initialize(gfx);
	jumping_animation_->GetImage().setScale(CAMERA_ZOOM);
}
