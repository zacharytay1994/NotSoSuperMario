#include "Mushroom.h"
#include <Windows.h>

Mushroom::Mushroom(ColliderManager& cm, const Vec2<float>& position, Mario& m)
	:
	cm_(&cm),
	GameObject("pictures\\supermushroom.png", 48, 48, 1, D3DXVECTOR2(position.x_, position.y_)),
	mario_(&m)
{
	// Initialize PhysicsComponent & add it to the Mushroom
	phy_ = new PhysicsComponent(*this);
	AddComponent(phy_);

	// Initialize CollisionDetectionComponent & add it to the Mushroom
	AddComponent(new CollisionDetectionComponent<AABBCollider>(*this, new AABBCollider(position_, this, sprite_->GetWidth() - 2, sprite_->GetHeight() - 2, false, true), cm));

	// Calculate direction
	direction_ = mario_->GetPosition().x > position_.x ? 1.0f : -1.0f;
}

void Mushroom::Update(const float& frametime)
{
	GameObject::Update(frametime);
	
	// Move
	phy_->AddVelocity(Vec2<float>(speed_ * direction_, 0.0f));

	// Mario x Mushroom collision: Mario goes Super
	if (touch_.touch_top_ && touch_obj_.touch_obj_top_->owner_->type_ == "Mario" || 
		touch_.touch_bottom_ && touch_obj_.touch_obj_bottom_->owner_->type_ == "Mario" || 
		touch_.touch_left_ && touch_obj_.touch_obj_left_->owner_->type_ == "Mario" || 
		touch_.touch_right_ && touch_obj_.touch_obj_right_->owner_->type_ == "Mario")
	{
			removed_ = true;

			// mario goes super
			mario_->ChangeSprite(mario_->super_idle_);
			mario_->hold_ = mario_->super_idle_;
			mario_->running_animation_ = mario_->super_running_animation_;
			mario_->jumping_ = mario_->super_jumping_;

			CollisionDetectionComponent<AABBCollider>* c = dynamic_cast<CollisionDetectionComponent<AABBCollider>*>(mario_->GetComponent("CollisionDetectionComponent"));
			c->SetColliderHeight(128 * CAMERA_ZOOM);

			mario_->is_big_ = true;
	}
	else if (touch_.touch_left_ && touch_obj_.touch_obj_left_->owner_->type_ != "Mario" || 
			 touch_.touch_right_ && touch_obj_.touch_obj_right_->owner_->type_ != "Mario")
	{
		direction_ *= -1.0f;
	}
}

void Mushroom::Render()
{
	GameObject::Render();

}

void Mushroom::ChildInitialize(Graphics& gfx)
{
	sprite_->Initialize(gfx);

}
