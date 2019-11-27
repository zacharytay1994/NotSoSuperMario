#include "Mario.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "CollisionDetectionComponent.h"

Mario::Mario(Input& input, ColliderManager& cm)
	:
	GameObject("pictures\\marioidle.png", 64, 64, 1, D3DXVECTOR2(200 * CAMERA_ZOOM, 100 * CAMERA_ZOOM)),
	running_animation_(new Sprite("pictures\\mariorunsheet.png", 64, 64, 3)),
	jumping_animation_(new Sprite("pictures\\mariojumping.png", 64, 64, 3))
{
	//sprite_.InitializeAnimation(0, 5, SHIP_ANIMATION_DELAY);
	running_animation_->InitializeAnimation(0, 5, 0.25f);
	AddComponent(new PhysicsComponent(*this));
	phy_ = dynamic_cast<PhysicsComponent*>(GetComponent("PhysicsComponent"));
	phy_->SetMass(10.0f);
	AddComponent(new InputComponent(*this, input));
	AddComponent(new CollisionDetectionComponent<AABBCollider>(*this, new AABBCollider(position_, this, sprite_->GetWidth() - 10.0f, sprite_->GetHeight(), false, true), cm));
}

Mario::~Mario()
{
	delete running_animation_;
	running_animation_ = nullptr;
	delete jumping_animation_;
	jumping_animation_ = nullptr;
}

void Mario::Update(const float& frametime)
{
	GameObject::Update(frametime);
	// temp
	if (looking_left) {
		sprite_->GetImage().flipHorizontal(false);
	}
	else {
		sprite_->GetImage().flipHorizontal(true);
	}
	ExecuteBounce();
}

void Mario::Render()
{
	GameObject::Render();
}

void Mario::ChildInitialize(Graphics& gfx)
{
	running_animation_->Initialize(gfx);
	running_animation_->GetImage().setScale(CAMERA_ZOOM);
	jumping_animation_->Initialize(gfx);
	jumping_animation_->GetImage().setScale(CAMERA_ZOOM);
}

void Mario::ExecuteBounce()
{
	if (bounce_off_others_) {
		phy_->AddVelocity(Vec2<float>( 0.0f, -1.0f ) * bounce_strength_);
		bounce_off_others_ = false;
	}
}
