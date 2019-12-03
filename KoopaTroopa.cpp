#include "KoopaTroopa.h"
#include "PhysicsComponent.h"
#include "CollisionDetectionComponent.h"
#include <cstdlib>
#include <iostream>
#include <sstream>

KoopaTroopa::KoopaTroopa(ColliderManager& cm, const Vec2<float>& position)
	:
	GameObject("pictures\\testsquare.png", 64, 64, 1, D3DXVECTOR2(position.x_, position.y_)),
	walking_sprite_(new Sprite("pictures\\kooparunsheet.png", 64, 64, 8)),
	shellmoving_sprite_(new Sprite("pictures\\koopashellmovingsheet.png", 54, 64, 4)),
	shellidle_sprite_(new Sprite("pictures\\koopashellidle.png", 54, 64, 1))
{
	//walking_sprite_->InitializeAnimation(0, 5, 0.25f);
	walking_sprite_->InitializeAnimation(0, 7, 0.25f);
	shellmoving_sprite_->InitializeAnimation(0, 3, 0.25f);

	PhysicsComponent* temp = new PhysicsComponent(*this);
	random = rand() % 5+10;
	timer = random;
	phy_ = temp;
	AddComponent(temp);
	AddComponent(new CollisionDetectionComponent<AABBCollider>(*this, new AABBCollider(position_, this, sprite_->GetWidth() - 10.0f, sprite_->GetHeight(), false, true), cm));
	sprite_ = walking_sprite_;
}

KoopaTroopa::~KoopaTroopa()
{

}

void KoopaTroopa::Update(const float& frametime)
{
	GameObject::Update(frametime);
	if (!shellState) {
		timer = timer - frametime;
		
		if (timer <= 0) {
			std::stringstream test;
			if (direction_.x_ == 1)
			{
				direction_.x_ = -1;
				sprite_->GetImage().flipHorizontal(false);
				looking_left_ = false;
			}
			else {
				direction_.x_ = 1;
				sprite_->GetImage().flipHorizontal(true);
				looking_left_ = false;
			}
			timer = random;
			
		}

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
			
			shellState = true;
		}


		// walk
		phy_->AddVelocity(direction_ * speed_);
	}
	
		else {
				// temp
				
				if (touch_.touch_left_) {
					direction_.x_ = -1;
					sprite_->GetImage().flipHorizontal(false);
					looking_left_ = true;
					shellMoving = true;
				}
				else if (touch_.touch_right_) {
					direction_.x_ = 1;
					sprite_->GetImage().flipHorizontal(true);
					looking_left_ = false;
					shellMoving = true;
				}
				if (touch_.touch_top_) {
					
					//sprite_->GetImage().flipVertical(!looking_left_);
					shellMoving = false;
				}

				
				if (!shellMoving) {
					ChangeSprite(shellidle_sprite_);
					phy_->AddVelocity(direction_ * 0); }
				else {
					ChangeSprite(shellmoving_sprite_);
					phy_->AddVelocity(direction_ * shellSpeed_); }
		}
	}

void KoopaTroopa::Render()
{
	GameObject::Render();
}

void KoopaTroopa::ChildInitialize(Graphics& gfx)
{
	shellidle_sprite_->Initialize(gfx);
	shellidle_sprite_->GetImage().setScale(CAMERA_ZOOM);
	shellmoving_sprite_->Initialize(gfx);
	shellmoving_sprite_->GetImage().setScale(CAMERA_ZOOM);
	walking_sprite_->Initialize(gfx);
	walking_sprite_->GetImage().setScale(CAMERA_ZOOM);

	
}
