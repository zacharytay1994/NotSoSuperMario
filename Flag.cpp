#include "Flag.h"
#include "CollisionDetectionComponent.h"
#include "Vec2.h"
#include "Scene.h"
#include "LevelOne.h"

Flag::Flag(ColliderManager& cm, const Vec2<float>& position, GameObject& mario, Scene& scene)
	:
	GameObject("pictures\\flagPole.png", 32, 640, 1, D3DXVECTOR2(position.x_, position.y_)),
	flagflag_(new Sprite("pictures\\flagflag.png", 64, 64, 1)),
	mario_(&mario),
	scene_(&scene)
{
	touch = false;
	flagdown = false;
	initialFlagHeight = sprite_->GetHeight() * 0.95 - flagflag_->GetHeight();
	flagrelativeposition = 1;
}

void Flag::Update(const float& frametime) {
	GameObject::Update(frametime);
	float const flagbottom = position_.y + sprite_->GetHeight() / 2;
	if (!touch) {
		/*float marioleft = mario_->sprite_->GetImage().getX() * CAMERA_ZOOM;
		float marioright = mario_->sprite_->GetImage().getX() * CAMERA_ZOOM + (mario_->sprite_->GetWidth() / 2);
		float mariotop = mario_->sprite_->GetImage().getY() * CAMERA_ZOOM - (mario_->sprite_->GetHeight() / 2);
		float mariobottom = mario_->sprite_->GetImage().getY() * CAMERA_ZOOM;*/
		float const marioleft = mario_->GetPosition().x - mario_->sprite_->GetWidth() / 2;
		float const marioright = mario_->GetPosition().x + mario_->sprite_->GetWidth() / 2;
		float const mariotop = mario_->GetPosition().y - mario_->sprite_->GetHeight() / 2;
		float const mariobottom = mario_->GetPosition().y + mario_->sprite_->GetHeight() / 2;

		/*float flagleft = sprite_->GetImage().getX() * CAMERA_ZOOM;
		float flagright = sprite_->GetImage().getX() * CAMERA_ZOOM + (sprite_->GetWidth() / 2);
		float flagtop = sprite_->GetImage().getY() * CAMERA_ZOOM - (sprite_->GetHeight() / 2);
		float flagbottom = sprite_->GetImage().getY() * CAMERA_ZOOM;*/
		float const flagleft = position_.x - sprite_->GetWidth() / 2;
		float const flagright = position_.x + sprite_->GetWidth() / 2;
		float const flagtop = position_.y - sprite_->GetHeight() / 2;
		//float const flagbottom = position_.y + sprite_->GetHeight() / 2;

		//if (!(marioright < flagleft || marioleft > flagright || mariobottom < flagtop || mariotop < flagbottom)) {
		if (!(marioleft > flagright || marioright < flagleft || mariotop > flagbottom || mariobottom < flagtop)){
			//contactdistance = position_.y + (sprite_->GetHeight()/2) -
			//	( mario_->GetPosition().y + (mario_->sprite_->GetHeight()/2));

			contactdistance = flagbottom - mariobottom;
			touch = true;
			
		}
	}
	
	if (touch && !flagdown) {

		flagrelativeposition -= 1.5 * frametime;
		
		mario_->SetPosition(mario_->GetPosition().x, flagbottom - (contactdistance * flagrelativeposition));
		dynamic_cast<PhysicsComponent*>(mario_->GetComponent("PhysicsComponent"))->SetVelocity(Vec2<float>(0.0f, 0.0f));

		if (flagrelativeposition <= 0) {
			flagdown = true;
			dynamic_cast<PhysicsComponent*>(mario_->GetComponent("PhysicsComponent"))->SetVelocity(Vec2<float>(1.0f, -1.0f) * 300);
			dynamic_cast<LevelOne*>(scene_)->levelCompleted = true;
		}

	}

	flagflag_->GetImage().setY(flagbottom - (initialFlagHeight * flagrelativeposition) - flagflag_->GetHeight());
}

void Flag::Render(){
	flagflag_->Draw();
	GameObject::Render();
}

void Flag::ChildInitialize(Graphics& gfx){
	GameObject::ChildInitialize(gfx);
	flagflag_->Initialize(gfx);
	flagflag_->GetImage().setScale(CAMERA_ZOOM);
	flagflag_->GetImage().setX(position_.x - flagflag_->GetWidth());
	flagflag_->GetImage().setY(position_.y + (sprite_->GetHeight()/2) - initialFlagHeight);
}
