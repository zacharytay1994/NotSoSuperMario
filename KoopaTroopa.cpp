#include "KoopaTroopa.h"
#include "PhysicsComponent.h"
#include "CollisionDetectionComponent.h"
#include <cstdlib>
#include <iostream>
#include <sstream>

KoopaTroopa::KoopaTroopa(ColliderManager& cm, const Vec2<float>& position)
	:
	GameObject("pictures\\" + theme + "\\testsquare.png", 64, 64, 1, D3DXVECTOR2(position.x_, position.y_), "Koopa"),
	walking_sprite_(new Sprite("pictures\\" + theme + "\\kooparunsheet.png", 64, 64, 8)),
	shellmoving_sprite_(new Sprite("pictures\\" + theme + "\\koopashellmovingsheet.png", 54, 64, 4)),
	shellidle_sprite_(new Sprite("pictures\\" + theme + "\\koopashellidle.png", 54, 64, 1))
	
{
	walking_sprite_->InitializeAnimation(0, 7, 0.25f);
	shellmoving_sprite_->InitializeAnimation(0, 3, 0.125f);

	PhysicsComponent* temp = new PhysicsComponent(*this);
	random = rand() % 5+10;
	timer = random;
	phy_ = temp;
	AddComponent(temp);
	AddComponent(new CollisionDetectionComponent<AABBCollider>(*this, new AABBCollider(position_, this, sprite_->GetWidth() - 10.0f, sprite_->GetHeight() - 3.0f, false, true), cm));
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
		if (touch_.touch_top_)
		{
			if (touch_obj_.touch_obj_top_->owner_->type_ == "Mario")
				shellState = true;
		}
		


		// walk
		phy_->AddVelocity(direction_ * speed_);
	}
	
		else {
			//dynamic_cast<CollisionDetectionComponent<AABBCollider>*>(GetComponent("CollisionDetectionComponent"));
;
				// temp
				
				if (touch_.touch_left_) {
					
					looking_left_ = true;
					shellMoving = true;
					if (touch_obj_.touch_obj_left_->owner_->type_ == "Goomba")
					{
						touch_obj_.touch_obj_left_->owner_->removed_ = true;
						//AddGoombaSprite();
					}
					else {
						direction_.x_ = -1;
						sprite_->GetImage().flipHorizontal(false);
						
					}
		
				}
				else if (touch_.touch_right_) {
			
					looking_left_ = false;
					shellMoving = true;
					
					if (touch_obj_.touch_obj_right_->owner_->type_ == "Goomba")
					{
						touch_obj_.touch_obj_right_->owner_->removed_ = true;
						//AddGoombaSprite();
					}
					else {
						direction_.x_ = 1;
						sprite_->GetImage().flipHorizontal(true);
					}
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
	UpdateGoombaSprites(frametime);
	}

void KoopaTroopa::Render()
{
	//DrawGoombaSprites();
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
	gfx_ = &gfx;
	
}

bool KoopaTroopa::GetShellState()
{
	return shellState;
}

bool KoopaTroopa::GetShellMovingState()
{
	return shellMoving;
}

void KoopaTroopa::AddGoombaSprite()
{
	Sprite* temp = new Sprite("pictures\\goombawalksheet.png", 64, 64, 4);
	temp->Initialize(*gfx_);
	temp->GetImage().setX(position_.x);
	temp->GetImage().setY(position_.y);
	temp->GetImage().setScale(CAMERA_ZOOM);
	goomba_sprites_.push_back(*temp);
}

void KoopaTroopa::UpdateGoombaSprites(const float& frametime)
{
	// loop through goombas
	for (int i = 0; i < goomba_sprites_.size(); i++) {
		// fly it up
		if (goomba_sprites_[i].GetImage().getRadians() < 1.571f) {
			goomba_sprites_[i].GetImage().setY(goomba_sprites_[i].GetImage().getY() - drop_speed_ * frametime);
		}
		else {
			drop_speed_ += 500.0f * frametime;
			goomba_sprites_[i].GetImage().setY(goomba_sprites_[i].GetImage().getY() + drop_speed_ * frametime);
		}
		// check if goomba rotation > certain amount, 270 degrees
		if (goomba_sprites_[i].GetImage().getRadians() > 15.652f) {
			// remove sprite
			Sprite* temp = &goomba_sprites_[i];
			goomba_sprites_.erase(goomba_sprites_.begin() + i);
			delete temp;
		}
		else {
			// spin it
			goomba_sprites_[i].GetImage().setRadians(goomba_sprites_[i].GetImage().getRadians() + 10.0f * frametime);
		}
	}
}

void KoopaTroopa::DrawGoombaSprites()
{
	for (int i = 0; i < goomba_sprites_.size(); i++) {
		goomba_sprites_[i].Draw();
	}
}
