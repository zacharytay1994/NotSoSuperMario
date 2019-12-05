#include "BouncyPlatform.h"
#include "CollisionDetectionComponent.h"
#include "PhysicsComponent.h"


BouncyPlatform::BouncyPlatform(ColliderManager& cm, const Vec2<float>& position)
	:
	GameObject("pictures\\springboard.png", 64, 64, 1, D3DXVECTOR2(position.x_, position.y_))
{
	sprite_->InitializeAnimation(0, 0, .15f);

	phy_ = new PhysicsComponent(*this, 0, false);
	AddComponent(phy_);

	// Initialize CollisionDetectionComponent & add it to the BouncyBlock
	AddComponent(new CollisionDetectionComponent<AABBCollider>(*this, new AABBCollider(position_, this, sprite_->GetWidth() - 10.0f, sprite_->GetHeight() + 2.0f, true, true, true), cm));
}





void BouncyPlatform::Update(const float& frametime)
{
	
	GameObject::Update(frametime);
	
	if (touch_.touch_top_) {
			PhysicsComponent* phy = dynamic_cast<PhysicsComponent*>(touch_obj_.touch_obj_top_->owner_->GetComponent("PhysicsComponent"));
			phy->AddVelocity(Vec2<float>(0.0f, -100.0f) * 100000);
		}
	
} 


void BouncyPlatform::Render()
{
	GameObject::Render();
}
void BouncyPlatform::ChildInitialize(Graphics& gfx)
{
	GameObject::ChildInitialize(gfx);
}