#include "QuestionMarkBlock.h"

QuestionMarkBlock::QuestionMarkBlock(ColliderManager& cm, const Vec2<float>& position, Scene& s, Mario& m)
	:
	cm_(&cm),
	GameObject("pictures\\questionmarkblock.png", 64, 64, 1, D3DXVECTOR2(position.x_, position.y_)),
	mario_(&m),
	scene_(&s),
	used_sprite_(new Sprite("pictures\\emptyquestionmarkblock.png", 64, 64, 1))
{
	// Initialize PhysicsComponent & add it to the Coin
	phy_ = new PhysicsComponent(*this, 0, false);
	AddComponent(phy_);

	// Initialize CollisionDetectionComponent & add it to the Coin
	AddComponent(new CollisionDetectionComponent<AABBCollider>(*this, new AABBCollider(position_, this, sprite_->GetWidth() - 1, sprite_->GetHeight(), true, true), cm));
}

void QuestionMarkBlock::Update(const float& frametime)
{
	GameObject::Update(frametime);

	// Check collision if unused
	if (!used_) 
	{
		// Question Mark block should disappear when bottom is collided with
		float cell_size_ = 64 * CAMERA_ZOOM;
		D3DXVECTOR2 mario_pos = mario_->GetPosition();
		if (mario_pos.x + cell_size_ >= position_.x && mario_pos.x <= position_.x + cell_size_ &&
			mario_pos.y <= position_.y + cell_size_ + 2 && mario_pos.y + cell_size_ + 2 >= position_.y + cell_size_)
		{
			// Update used_ flag
			used_ = true;

			// Change sprite of block
			ChangeSprite(used_sprite_);

			// TODO: Spawn mushroom on top of block
			scene_->AddObjectToScene(*(new Goomba(*cm_, Vec2<float>(position_.x, position_.y - cell_size_ - 2.0f))));
		}
	}

}

void QuestionMarkBlock::Render()
{
	GameObject::Render();

}

void QuestionMarkBlock::ChildInitialize(Graphics& gfx)
{
	GameObject::ChildInitialize(gfx);

	sprite_->Initialize(gfx);
	used_sprite_->Initialize(gfx);
	used_sprite_->GetImage().setScale(CAMERA_ZOOM);
}