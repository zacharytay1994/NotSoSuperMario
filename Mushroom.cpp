#include "Mushroom.h"

Mushroom::Mushroom(ColliderManager& cm, const Vec2<float>& position, Mario& m)
	:
	cm_(&cm),
	GameObject("pictures\\supermushroom.png", 64, 64, 1, D3DXVECTOR2(position.x_, position.y_)),
	mario_(&m)
{
	// Initialize PhysicsComponent & add it to the Mushroom
	phy_ = new PhysicsComponent(*this, 0, false);
	AddComponent(phy_);

	// Initialize CollisionDetectionComponent & add it to the Mushroom
	AddComponent(new CollisionDetectionComponent<AABBCollider>(*this, new AABBCollider(position_, this, sprite_->GetWidth() - 1, sprite_->GetHeight() - 6, false, false), cm));
}

void Mushroom::Update(const float& frametime)
{
	GameObject::Update(frametime);

	// TODO: if collided with, mario goes Super
	if (touch_.touch_top_ || touch_.touch_bottom_ || touch_.touch_left_ || touch_.touch_right_)
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
}

void Mushroom::Render()
{
	GameObject::Render();

}

void Mushroom::ChildInitialize(Graphics& gfx)
{
	sprite_->Initialize(gfx);

}
