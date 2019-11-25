#include "Goomba.h"
#include "PhysicsComponent.h"
#include "CollisionDetectionComponent.h"

Goomba::Goomba(Input& input, ColliderManager& cm, const Vec2<float>& position)
	:
	GameObject("pictures\\testsquare.png", 64, 64, 1, D3DXVECTOR2(position.x_ * CAMERA_ZOOM, position.y_ * CAMERA_ZOOM)),
	walking_sprite_(new Sprite("pictures\\goombawalksheet.png", 64, 64, 4))
{
	//walking_sprite_->InitializeAnimation(0, 5, 0.25f);
	walking_sprite_->InitializeAnimation(0, 5, 0.25f);
	PhysicsComponent* temp = new PhysicsComponent(*this);
	phy_ = temp;
	AddComponent(temp);
	AddComponent(new CollisionDetectionComponent<AABBCollider>(*this, new AABBCollider(position_, this, sprite_->GetWidth(), sprite_->GetHeight(), false, true), cm));
	sprite_ = walking_sprite_;
}

Goomba::~Goomba()
{
}

void Goomba::Update(const float& frametime)
{
	GameObject::Update(frametime);
	// temp
	if (touch_.touch_left_) {
		direction_.x_ = -1;
		sprite_->GetImage().flipHorizontal(false);
	}
	else if (touch_.touch_right_) {
		direction_.x_ = 1;
		sprite_->GetImage().flipHorizontal(true);
	}
	if (touch_.touch_top_) {
		removed_ = true;
	}
	// walk
	phy_->AddVelocity(direction_ * speed_);
}

void Goomba::Render()
{
	GameObject::Render();
}

void Goomba::ChildInitialize(Graphics& gfx)
{
	walking_sprite_->Initialize(gfx);
	walking_sprite_->GetImage().setScale(CAMERA_ZOOM);
}
