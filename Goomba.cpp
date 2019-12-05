#include "Goomba.h"
#include "PhysicsComponent.h"
#include "CollisionDetectionComponent.h"

Goomba::Goomba(ColliderManager& cm, const Vec2<float>& position)
	:
	GameObject("pictures\\testsquare.png", 64, 64, 1, D3DXVECTOR2(position.x_, position.y_), "Goomba"),
	walking_sprite_(new Sprite("pictures\\goombawalksheet.png", 64, 64, 4)),
	death_sprite_(new Sprite("pictures\\goombadeath.png", 64, 64, 1))
{
	//walking_sprite_->InitializeAnimation(0, 5, 0.25f);
	walking_sprite_->InitializeAnimation(0, 5, 0.25f);
	PhysicsComponent* temp = new PhysicsComponent(*this);
	phy_ = temp;
	AddComponent(temp);
	AddComponent(new CollisionDetectionComponent<AABBCollider>(*this, new AABBCollider(position_, this, sprite_->GetWidth() - 10.0f, sprite_->GetHeight(), false, true), cm));
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
		looking_left_ = true;
	}
	else if (touch_.touch_right_) {
		direction_.x_ = 1;
		sprite_->GetImage().flipHorizontal(true);
		looking_left_ = false;
	}

	if (touch_.touch_top_) {
		pend_removal_ = true;
		ChangeSprite(death_sprite_);
		sprite_->GetImage().flipHorizontal(!looking_left_);
	}
	// walk
	if (!pend_removal_) {
		phy_->AddVelocity(direction_ * speed_);
	}
	
}

void Goomba::Render()
{
	GameObject::Render();
}

void Goomba::ChildInitialize(Graphics& gfx)
{
	walking_sprite_->Initialize(gfx);
	walking_sprite_->GetImage().setScale(CAMERA_ZOOM);
	death_sprite_->Initialize(gfx);
	death_sprite_->GetImage().setScale(CAMERA_ZOOM);
}
