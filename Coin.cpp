#include "Coin.h"

Coin::Coin(Input& input, ColliderManager& cm, const Vec2<float>& position)
	:
	GameObject("pictures\\coinsheet.png", 64, 64, 4, D3DXVECTOR2(position.x_* CAMERA_ZOOM, position.y_* CAMERA_ZOOM))
{
	sprite_->InitializeAnimation(0, 3, .15f);
}

void Coin::Update(const float& frametime)
{
	GameObject::Update(frametime);

}

void Coin::Render()
{
	GameObject::Render();

}

void Coin::ChildInitialize(Graphics& gfx)
{
	GameObject::ChildInitialize(gfx);

}