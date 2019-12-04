#include "Coin.h"
#include "CollisionDetectionComponent.h"

Coin::Coin(ColliderManager& cm, const Vec2<float>& position, ScoreManager* sm)
	:
	GameObject("pictures\\coinsheet.png", 64, 64, 4, D3DXVECTOR2(position.x_, position.y_), "Coin"),
	score_manager_(sm)
{
	// Begin animating Coin sprite
	sprite_->InitializeAnimation(0, 3, .15f);

	// Initialize PhysicsComponent & add it to the Coin
	phy_ = new PhysicsComponent(*this, 0, false);
	AddComponent(phy_);

	// Initialize CollisionDetectionComponent & add it to the Coin
	AddComponent(new CollisionDetectionComponent<AABBCollider>(*this, new AABBCollider(position_, this, sprite_->GetWidth() - 10.0f, sprite_->GetHeight() - 10.0f, false, false), cm));
}

void Coin::Update(const float& frametime)
{
	GameObject::Update(frametime);

	// Coin x Mario: Coin collected
	if (touch_.touch_top_ && touch_obj_.touch_obj_top_->owner_->type_ == "Mario" || 
		touch_.touch_bottom_ && touch_obj_.touch_obj_bottom_->owner_->type_ == "Mario" ||
		touch_.touch_left_ && touch_obj_.touch_obj_left_->owner_->type_ == "Mario" ||
		touch_.touch_right_ && touch_obj_.touch_obj_right_->owner_->type_ == "Mario")
	{
		// Destroy coin
		removed_ = true;

		// Increment score
		score_manager_->IncrementScore();
	}
}

void Coin::Render()
{
	GameObject::Render();

}

void Coin::ChildInitialize(Graphics& gfx)
{
	GameObject::ChildInitialize(gfx);

}