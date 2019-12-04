#include "Mario.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "CollisionDetectionComponent.h"
#include <string>
#include <iostream>
#include <sstream>

Mario::Mario(Input& input, ColliderManager& cm)
	:
	GameObject("pictures\\marioidle.png", 64, 64, 1, D3DXVECTOR2(200 * CAMERA_ZOOM, 100 * CAMERA_ZOOM), "Mario"),
	normal_idle_(new Sprite("pictures\\marioidle.png", 64, 64, 1)),
	normal_running_animation_(new Sprite("pictures\\mariorunsheet.png", 64, 64, 3)),
	normal_jumping_animation_(new Sprite("pictures\\mariojumping.png", 64, 64, 3)),

	super_idle_(new Sprite("pictures\\supermarioidle.png", 64, 128, 1)),
	super_jumping_(new Sprite("pictures\\supermariojumping.png", 64, 128, 1)),
	super_running_animation_(new Sprite("pictures\\supermariorunsheet.png", 64, 128, 3)),

	idle_(normal_idle_),
	jumping_(normal_jumping_animation_),
	running_animation_(normal_running_animation_)
{
	//sprite_.InitializeAnimation(0, 5, SHIP_ANIMATION_DELAY);
	normal_running_animation_->InitializeAnimation(0, 5, 0.25f);
	super_running_animation_->InitializeAnimation(0, 2, 0.25f);
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
	GameObject::Update(frametime);
	/*position_.x = 0.0f;
	position_.y = 0.0f;*/
	// temp
	if (looking_left) {
		sprite_->GetImage().flipHorizontal(false);
	}
	else {
		sprite_->GetImage().flipHorizontal(true);
	}
	ExecuteBounce();
	/*D3DXVECTOR2 test = dynamic_cast<CollisionDetectionComponent<AABBCollider>*>(GetComponent("CollisionDetectionComponent"))->GetCollider()->center_point;
	std::stringstream ss;
	ss << "COLLIDER: " << test.x << "," << test.y << std::endl;
	ss << "POSITION: " << position_.x << "," << position_.y << std::endl;
	ss << "SPRITEPOS: " << sprite_->GetImage().getX() << "," << sprite_->GetImage().getY() << std::endl;*/
	//OutputDebugString(ss.str().c_str());
}

void Mario::Render()
{
	GameObject::Render();
}

void Mario::ChildInitialize(Graphics& gfx)
{
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
}

void Mario::ExecuteBounce()
{
	if (bounce_off_others_) {
		phy_->AddVelocity(Vec2<float>( 0.0f, -1.0f ) * bounce_strength_);
		bounce_off_others_ = false;
	}
}
