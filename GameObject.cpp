#include "GameObject.h"
#include "constants.h"

GameObject::GameObject(const std::string& path, const int& width, const int& height, const int& cols, D3DXVECTOR2& pos)
	:
	position_(pos),
	sprite_(new Sprite(path, width, height, cols)),
	hold_(sprite_)
{
}

GameObject::~GameObject()
{
	for each (Component* c in components_) {
		delete c;
		c = nullptr;
	}
	delete sprite_;
	sprite_ = nullptr;
	if (hold_ != nullptr) {
		delete hold_;
		hold_ = nullptr;
	}
}

void GameObject::Update(const float& frametime)
{
	ProcessOnGround(frametime);
	for each (Component * c in components_) {
		if (c != nullptr) {
			c->Update(frametime);
		}
	}
	sprite_->Update(frametime);
	SyncSprite();
}

void GameObject::Render()
{
	for each (Component * c in components_) {
		if (c != nullptr) {
			c->Draw();
		}
	}
	sprite_->Draw();
}

void GameObject::Initialize(Graphics& gfx)
{
	sprite_->Initialize(gfx);
	sprite_->GetImage().setX(position_.x);
	sprite_->GetImage().setY(position_.y);
	sprite_->GetImage().setScale(CAMERA_ZOOM);
	ChildInitialize(gfx);
}

void GameObject::ChildInitialize(Graphics& gfx)
{
}

void GameObject::AddComponent(Component* component)
{
	components_.push_back(component);
}

Component* GameObject::GetComponent(std::string type)
{
	for each (Component * c in components_) {
		if (c->GetType() == type) {
			return c;
		}
	}
	return nullptr;
}

void GameObject::SyncSprite()
{
	sprite_->GetImage().setX(position_.x - sprite_->GetImage().getWidth()/2);
	sprite_->GetImage().setY(position_.y - sprite_->GetImage().getHeight()/2);
}

void GameObject::ChangeSprite(Sprite* sprite)
{
	sprite_ = sprite;
}

void GameObject::ProcessOnGround(const float& frametime)
{
	if (!touched_ground_) {
		air_time_ += frametime;
	}
	else {
		air_time_ = 0.0f;
		on_ground_ = true;
	}
	if (air_time_ > 0.2f) {
		on_ground_ = false;
	}
}

void GameObject::SetPosition(const float& x, const float& y)
{
	position_.x = x;
	position_.y = y;
}

D3DXVECTOR2 GameObject::GetPosition()
{
	return position_;
}

void GameObject::TellComponents(Component::Message msg){
	for each (Component * c in components_) {
		if (c != nullptr) {
			c->ReceiveMessage(msg);
		}
	}
}
