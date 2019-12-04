#include "Flag.h"
#include "CollisionDetectionComponent.h"
#include "Vec2.h"

Flag::Flag(ColliderManager& cm, const Vec2<float>& position, GameObject* mario)
	:
	GameObject("pictures\\flagPole.png", 32, 640, 1, D3DXVECTOR2(position.x_ * CAMERA_ZOOM, position.y_ * CAMERA_ZOOM)),
	flagflag_(new Sprite("pictures\\flagflag.png", 64, 64, 1))
{
	mario_ = mario;
	touch = false;
	flagdown = false;
	initialFlagHeight = sprite_->GetHeight() * 0.95 - flagflag_->GetHeight();
	flagrelativeposition = .4;
}

void Flag::Update(const float& frametime) {
	GameObject::Update(frametime);
	if (!touch) {
		float marioleft = mario_->sprite_->GetImage().getX();
		float marioright = mario_->sprite_->GetImage().getX() + (mario_->sprite_->GetWidth() / 2);
		float mariotop = mario_->sprite_->GetImage().getY() - (mario_->sprite_->GetHeight() / 2);
		float mariobottom = mario_->sprite_->GetImage().getY();

		float flagleft = sprite_->GetImage().getX();
		float flagright = sprite_->GetImage().getX() + (sprite_->GetWidth() / 2);
		float flagtop = sprite_->GetImage().getY() - (sprite_->GetHeight() / 2);
		float flagbottom = sprite_->GetImage().getY();
		if (!(marioright < flagleft || marioleft > flagright || mariobottom < flagtop || mariotop < flagbottom)) {
			contactdistance = position_.y - mario_->GetPosition().y;
			touch = true;
			
		}
	}
	
	if (touch && !flagdown) {

		flagrelativeposition -= 1.5 * frametime;
		mario_->SetPosition(mario_->GetPosition().x, position_.y - (contactdistance * flagrelativeposition));
		dynamic_cast<PhysicsComponent*>(mario_->GetComponent("PhysicsComponent"))->SetVelocity(Vec2<float>(0.0f, 0.0f));

		if (flagrelativeposition <= -.57) {
			flagdown = true;
			dynamic_cast<PhysicsComponent*>(mario_->GetComponent("PhysicsComponent"))->SetVelocity(Vec2<float>(1.0f, -1.0f) * 300);
		}

	}

	flagflag_->GetImage().setY(position_.y - (initialFlagHeight * flagrelativeposition) - flagflag_->GetHeight());
}

void Flag::Render(){
	flagflag_->Draw();
	GameObject::Render();
}

void Flag::ChildInitialize(Graphics& gfx){
	GameObject::ChildInitialize(gfx);
	flagflag_->Initialize(gfx);
	flagflag_->GetImage().setScale(CAMERA_ZOOM);
	flagflag_->GetImage().setX(position_.x - flagflag_->GetWidth() - (sprite_->GetWidth()/2));
	flagflag_->GetImage().setY(position_.y - initialFlagHeight);
}
