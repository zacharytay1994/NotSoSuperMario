#include "GameObject.h"
#include "constants.h"
#include <mmsystem.h>

GameObject::GameObject(const std::string& path, const int& width, const int& height, const int& cols, D3DXVECTOR2& pos, std::string t)
	:
	position_(pos),
	sprite_(new Sprite(path, width, height, cols)),
	hold_(sprite_),
	type_(t)
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
	PendRemoval(frametime);
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
	sprite_->GetImage().setX(position_.x - sprite_->GetImage().getWidth()/2*CAMERA_ZOOM);
 	sprite_->GetImage().setY(position_.y - sprite_->GetImage().getHeight()/2*CAMERA_ZOOM);
}

void GameObject::ChangeSprite(Sprite* sprite)
{
	sprite_ = sprite;
}

void GameObject::ProcessOnGround(const float& frametime)
{
	if (!touch_.touch_bottom_) {
		air_time_ += 0.006f;

	}
	else {
		air_time_ = 0.0f;
		on_ground_ = true;
		
	}
	if (air_time_ > 0.2f) {
		on_ground_ = false;
		

	}
	if (air_time_ > 0.05f)
	{
		if (!start_air_time_)
		{
			if (type_ == "Mario")
			{
				PlaySound("sounds\\smb_jump-super.wav", NULL, SND_FILENAME || SND_ASYNC);
				start_air_time_ = true;
			}
		}
	}
	else
	{
		start_air_time_ = false;
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

void GameObject::PendRemoval(const float& frametime)
{
	if (pend_removal_) {
		if (death_timer_ > 0.0f) {
			death_timer_ -= frametime;
		}
		else {
			removed_ = true;
		}
	}
}
