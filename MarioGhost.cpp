#include "MarioGhost.h"

MarioGhost::MarioGhost()
	:
	GameObject("pictures\\marioidle.png", 64, 64, 1, D3DXVECTOR2(200 * CAMERA_ZOOM, 100 * CAMERA_ZOOM))
{
}

MarioGhost::~MarioGhost()
{
}

void MarioGhost::Update(const float& frametime)
{
	GameObject::Update(frametime);
}

void MarioGhost::Render()
{
	GameObject::Render();
}
