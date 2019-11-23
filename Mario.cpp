#include "Mario.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "CollisionDetectionComponent.h"

Mario::Mario(Input& input, ColliderManager& cm)
	:
	GameObject("pictures\\testsquare.png", 64, 64, 1, D3DXVECTOR2(GAME_WIDTH / 2, GAME_HEIGHT/2))
{
	//sprite_.InitializeAnimation(0, 5, SHIP_ANIMATION_DELAY);
	AddComponent(new PhysicsComponent(*this));
	AddComponent(new InputComponent(*this, input));
	AddComponent(new CollisionDetectionComponent<AABBCollider>(*this, new AABBCollider(position_, this, sprite_.GetWidth(), sprite_.GetHeight(), false, true), cm));
}

Mario::~Mario()
{
}

void Mario::Update(const float& frametime)
{
	GameObject::Update(frametime);
}

void Mario::Render()
{
	GameObject::Render();
}
