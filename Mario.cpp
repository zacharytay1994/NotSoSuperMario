#include "Mario.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "CollisionDetectionComponent.h"
#include "KoopaTroopa.h"
#include <Windows.h>
#include <chrono>
#include <thread>
#include <string>
#include <iostream>
#include <sstream>

Mario::Mario(Input& input, ColliderManager& cm)
	:
	GameObject("pictures\\marioidle.png", 64, 64, 1, D3DXVECTOR2(200 * CAMERA_ZOOM, 100 * CAMERA_ZOOM), "Mario"),
	dying_sprite(new Sprite("pictures\\marioDeath.png", 64, 64, 1)),
	
	normal_idle_(new Sprite("pictures\\marioidle.png", 64, 64, 1)),
	normal_running_animation_(new Sprite("pictures\\mariorunsheet.png", 64, 64, 3)),
	normal_jumping_animation_(new Sprite("pictures\\mariojumping.png", 64, 64, 3)),

	super_idle_(new Sprite("pictures\\supermarioidle.png", 64, 128, 1)),
	super_jumping_(new Sprite("pictures\\supermariojumping.png", 64, 128, 1)),
	super_running_animation_(new Sprite("pictures\\supermariorunsheet.png", 64, 128, 3)),

	idle_(normal_idle_),
	jumping_(normal_jumping_animation_),
	running_animation_(normal_running_animation_),

	growing_animation_(new Sprite("pictures\\marioGrowing.png", 64, 128, 5))
{
	//sprite_.InitializeAnimation(0, 5, SHIP_ANIMATION_DELAY);
	normal_running_animation_->InitializeAnimation(0, 5, 0.25f);
	super_running_animation_->InitializeAnimation(0, 2, 0.25f);
	growing_animation_->InitializeAnimation(0, 4, 0.25f);
	AddComponent(new PhysicsComponent(*this));
	phy_ = dynamic_cast<PhysicsComponent*>(GetComponent("PhysicsComponent"));
	phy_->SetMass(10.0f);
	AddComponent(new InputComponent(*this, input));
	AddComponent(new CollisionDetectionComponent<AABBCollider>(*this, new AABBCollider(position_, this, sprite_->GetWidth() - 10.0f, sprite_->GetHeight(), false, true), cm));
}

Mario::~Mario()
{
	delete normal_running_animation_;
	normal_running_animation_ = nullptr;
	delete normal_jumping_animation_;
	normal_jumping_animation_ = nullptr;
}

void Mario::Update(const float& frametime)
{
	if (!isTouchedGoomba)
	{
		GameObject::Update(frametime);

		// temp
		if (looking_left)
		{
			sprite_->GetImage().flipHorizontal(false);
		}
		else
		{
			sprite_->GetImage().flipHorizontal(true);
		}

		// If mario touch goomba with left/right side, mario is dead
		if (!isInvicible)
		{

			if (touch_.touch_left_)

			{
				if (touch_obj_.touch_obj_left_->owner_->type_ == "Goomba")
				{
					isTouchedGoomba = true;
				}

				else if (touch_obj_.touch_obj_left_->owner_->type_ == "Koopa")
				{
					if (dynamic_cast<KoopaTroopa*>(touch_obj_.touch_obj_left_->owner_)->GetShellState())
					{
						if (dynamic_cast<KoopaTroopa*>(touch_obj_.touch_obj_left_->owner_)->GetShellMovingState())
						{
							isTouchedGoomba = true;
						}
					}
					else
					{
						isTouchedGoomba = true;
					}
				}

			}

			else if (touch_.touch_right_)
			{
				if (touch_obj_.touch_obj_right_->owner_->type_ == "Goomba")
				{
					isTouchedGoomba = true;
				}
				else if (touch_obj_.touch_obj_right_->owner_->type_ == "Koopa")
				{
					if (dynamic_cast<KoopaTroopa*>(touch_obj_.touch_obj_right_->owner_)->GetShellState())
					{
						if (dynamic_cast<KoopaTroopa*>(touch_obj_.touch_obj_right_->owner_)->GetShellMovingState())
						{
							isTouchedGoomba = true;
						}
					}
					else
					{
						isTouchedGoomba = true;
					}
				}
			}
		}
	}

	// When mario is dead, play the mario deadth animation once

	if (!is_big_)
	{
		if (isTouchedGoomba)
		{
			is_dead_ = true;

			if (!deathAnimationDone)
			{
				dying_sprite->GetImage().setX(sprite_->GetImage().getX());
				dying_sprite->GetImage().setY(sprite_->GetImage().getY());

				turn_radius_ += turn_rate_ * frametime;

				deadVel += velocity * frametime;
				dying_sprite->GetImage().setDegrees(turn_radius_);
				if (velocity > -1000)
				{
					dying_sprite->GetImage().setY(dying_sprite->GetImage().getY() - deadVel);
					velocity -= 5;
				}
				else
				{
					deathAnimationDone = true;
					
					// set mario outside of screen after the animation is done
					dying_sprite->GetImage().setX(GAME_WIDTH);
					dying_sprite->GetImage().setY(GAME_HEIGHT);

				}
			}
		}


		
		
		/*D3DXVECTOR2 test = dynamic_cast<CollisionDetectionComponent<AABBCollider>*>(GetComponent("CollisionDetectionComponent"))->GetCollider()->center_point;
		std::stringstream ss;
		ss << "COLLIDER: " << test.x << "," << test.y << std::endl;
		ss << "POSITION: " << position_.x << "," << position_.y << std::endl;
		ss << "SPRITEPOS: " << sprite_->GetImage().getX() << "," << sprite_->GetImage().getY() << std::endl;*/
		//OutputDebugString(ss.str().c_str());
	}
	else
	{
		if (!isAnimComplete)
		{
			hold_ = growing_animation_;
		}
		if (hold_->GetImage().getAnimationComplete())
		{

			ChangeSprite(super_idle_);
			hold_ = super_idle_;
			running_animation_ = super_running_animation_;
			jumping_ = super_jumping_;
			isAnimComplete = true;

		}


		if (isTouchedGoomba)
		{
			ChangeSprite(normal_idle_);
			hold_ = normal_idle_;
			running_animation_ = normal_running_animation_;
			jumping_ = normal_jumping_animation_;
			is_big_ = false;
			isInvicible = true;
			CollisionDetectionComponent<AABBCollider>* c = dynamic_cast<CollisionDetectionComponent<AABBCollider>*>(GetComponent("CollisionDetectionComponent"));
			c->SetColliderHeight(64 * CAMERA_ZOOM);
			checkOneSec = true;
			isTouchedGoomba = false;

		}

	}
	if (checkOneSec)
	{
		oneSec = oneSec - frametime;
	}
	if (oneSec < 0)
	{
		isInvicible = false;
		checkOneSec = false;
		oneSec = 1;
	}
	ExecuteBounce();
}


void Mario::Render()
{
	if (!isTouchedGoomba)
	{
		GameObject::Render();
	}
	else if (is_big_)
	{
		GameObject::Render();
	}
	else if (isTouchedGoomba)
	{
		dying_sprite->Draw();
	}
}

void Mario::ChildInitialize(Graphics& gfx)
{
	dying_sprite->Initialize(gfx);
	dying_sprite->GetImage().setScale(CAMERA_ZOOM);

	normal_idle_->Initialize(gfx);
	normal_idle_->GetImage().setScale(CAMERA_ZOOM);
	normal_running_animation_->Initialize(gfx);
	normal_running_animation_->GetImage().setScale(CAMERA_ZOOM);
	normal_jumping_animation_->Initialize(gfx);
	normal_jumping_animation_->GetImage().setScale(CAMERA_ZOOM);

	super_idle_->Initialize(gfx);
	super_idle_->GetImage().setScale(CAMERA_ZOOM);
	super_running_animation_->Initialize(gfx);
	super_running_animation_->GetImage().setScale(CAMERA_ZOOM);
	super_jumping_->Initialize(gfx);
	super_jumping_->GetImage().setScale(CAMERA_ZOOM);

	growing_animation_->Initialize(gfx);
	growing_animation_->GetImage().setScale(CAMERA_ZOOM);
}

void Mario::ExecuteBounce()
{
	if (bounce_off_others_) {
		phy_->AddVelocity(Vec2<float>( 0.0f, -1.0f ) * bounce_strength_);
		bounce_off_others_ = false;
	}
}
