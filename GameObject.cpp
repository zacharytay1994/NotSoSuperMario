#include "GameObject.h"

GameObject::GameObject(const std::string& path, const int& width, const int& height, const int& cols, D3DXVECTOR2& pos)
	:
	position_(pos),
	sprite_(path, width, height, cols)
{
}

GameObject::~GameObject()
{
	for each (Component* c in components_) {
		c = nullptr;
		delete c;
	}
}

void GameObject::Update(const float& frametime)
{
	for each (Component * c in components_) {
		if (c != nullptr) {
			c->Update(frametime);
		}
	}
	sprite_.Update(frametime);
	SyncSprite();
}

void GameObject::Render()
{
	for each (Component * c in components_) {
		if (c != nullptr) {
			c->Draw();
		}
	}
	sprite_.Draw();
}

void GameObject::Initialize(Graphics& gfx)
{
	sprite_.Initialize(gfx);
	sprite_.GetImage().setX(position_.x);
	sprite_.GetImage().setY(position_.y);
}

void GameObject::AddComponent(Component& component)
{
	components_.push_back(&component);
}

void GameObject::SyncSprite()
{
	sprite_.GetImage().setX(position_.x);
	sprite_.GetImage().setY(position_.y);
}

void GameObject::SetPosition(const float& x, const float& y)
{
	position_.x = x;
	position_.y = y;
}

D3DXVECTOR2 GameObject::GetPosiiton()
{
	return position_;
}
