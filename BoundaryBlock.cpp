#include "BoundaryBlock.h"
#include "CollisionDetectionComponent.h"

BoundaryBlock::BoundaryBlock(ColliderManager& cm, const Vec2<float>& position)
	:
	GameObject("pictures\\testsquare.png", 64, 64, 4, D3DXVECTOR2(position.x_, position.y_))
{
	sprite_->InitializeAnimation(0, 3, .15f);

	phy_ = new PhysicsComponent(*this, 0, false);
	AddComponent(phy_);

	// Initialize CollisionDetectionComponent & add it to the BoundaryBlock
	AddComponent(new CollisionDetectionComponent<AABBCollider>(*this, new AABBCollider(position_, this, sprite_->GetWidth() - 10.0f, sprite_->GetHeight() - 10.0f, false, false), cm));
}

void BoundaryBlock::Update(const float& frametime)
{
	GameObject::Update(frametime);


	if (touch_.touch_top_ || touch_.touch_bottom_ || touch_.touch_left_ || touch_.touch_right_)
	{
	}
}

void BoundaryBlock::Render()
{
	GameObject::Render();
}

void BoundaryBlock::ChildInitialize(Graphics& gfx)
{
	GameObject::ChildInitialize(gfx);
}