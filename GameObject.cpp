#include "GameObject.h"

GameObject::GameObject(const std::string& path, const int& width, const int& height, const int& cols, D3DXVECTOR2& pos)
	:
	position_(pos),
	sprite_(path, width, height, cols)
{
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
	sprite_.Update(1 / 60);
	sprite_.SetX(sprite_.GetX() + 1);
}

void GameObject::Render()
{
	sprite_.Draw();
}

void GameObject::Initialize(Graphics& gfx)
{
	sprite_.Initialize(gfx);
	sprite_.SetX(position_.x);
	sprite_.SetY(position_.y);
}
