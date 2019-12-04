#include "BouncyPlatform.h"
#include "CollisionDetectionComponent.h"
#include "PhysicsComponent.h"


BouncyPlatform::BouncyPlatform(ColliderManager& cm, const Vec2<float>& position)
	:
	GameObject("pictures\\testsquare.png", 64, 64, 4, D3DXVECTOR2(position.x_, position.y_))
{
	sprite_->InitializeAnimation(0, 3, .15f);

	phy_ = new PhysicsComponent(*this,-1, false);
	AddComponent(phy_);

	// Initialize CollisionDetectionComponent & add it to the BoundaryBlock
	AddComponent(new CollisionDetectionComponent<AABBCollider>(*this, new AABBCollider(position_, this, sprite_->GetWidth() - 10.0f, sprite_->GetHeight() - 10.0f, false, true), cm));
}





void BouncyPlatform::Update(const float& frametime)
{
	
	GameObject::Update(frametime);
	
	if (touch_.touch_top_) {
	
			PhysicsComponent* phy = dynamic_cast<PhysicsComponent*>(touch_obj_.touch_obj_top_->owner_->GetComponent("PhysicsComponent"));
			phy->AddVelocity(Vec2<float>(0.0f, -100.0f) * 100);

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