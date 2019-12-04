#include "QuestionMarkBlock.h"
#include "LevelOne.h"

QuestionMarkBlock::QuestionMarkBlock(ColliderManager& cm, const Vec2<float>& position, Scene& s, Mario& m)
	:
	cm_(&cm),
	GameObject("pictures\\questionmarkblock.png", 64, 64, 6, D3DXVECTOR2(position.x_, position.y_)),
	mario_(&m),
	scene_(&s),
	used_sprite_(new Sprite("pictures\\emptyquestionmarkblock.png", 64, 64, 1))
{
	// Initialize sprite
	sprite_->InitializeAnimation(0, 5, .15f);

	// Initialize PhysicsComponent & add it to the Question Mark block
	phy_ = new PhysicsComponent(*this, 0, false);
	AddComponent(phy_);

	// Initialize CollisionDetectionComponent & add it to the Question Mark block
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
		if (mario_pos.x + mario_->sprite_->GetWidth() / 2 >= position_.x && // mario's R >= block's L
			mario_pos.x <= position_.x + sprite_->GetWidth() / 2 && // mario's L <= block's R
			mario_pos.y - mario_->sprite_->GetHeight() / 2 <= position_.y + sprite_->GetHeight() / 2 + 2 && // mario's T <= block's B
			mario_pos.y + mario_->sprite_->GetHeight() / 2 >= position_.y) // mario's B >= block's T
		{
			// Update used_ flag
			used_ = true;

			// Set airtime & halfairtime
			curr_frame_ = airtime_;

			// Change sprite of block
			ChangeSprite(used_sprite_);

			// Check mario type
			if (mario_->is_big_)
			{
				// Spawn coin on top of block
				LevelOne* lvlOne = dynamic_cast<LevelOne*>(scene_);
				scene_->AddObjectToScene(*(new Coin(*cm_, Vec2<float>(position_.x, position_.y - cell_size_), lvlOne->score_manager_)));
			}
			else
			{
				// Spawn mushroom on top of block
				scene_->AddObjectToScene(*(new Mushroom(*cm_, Vec2<float>(position_.x, position_.y - cell_size_), *mario_)));
			}
		}
	}
	else
	{
		if (curr_frame_ > 0)
		{
			// Update airtime
			curr_frame_--;

			// Apply upward force
			phy_->SetVelocity(Vec2<float>(0.0f, 10.0f * -(curr_frame_ - airtime_ / 2)));
		}
		else if (curr_frame_ == 0)
		{
			phy_->SetVelocity(Vec2<float>(0.0f, 0.0f));
			position_.y--;
			curr_frame_ = -1;
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

	used_sprite_->Initialize(gfx);
	used_sprite_->GetImage().setScale(CAMERA_ZOOM);
}