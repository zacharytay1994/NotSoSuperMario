#include "Mario.h"
#include "InputComponent.h"
#include "CollisionDetectionComponent.h"

Mario::Mario(Input& input, ColliderManager& cm)
	:
	GameObject("pictures\\testsquare.png", 128, 128, 1, D3DXVECTOR2(GAME_WIDTH / 4, GAME_HEIGHT / 4))
{
	//sprite_.InitializeAnimation(0, 5, SHIP_ANIMATION_DELAY);
	AddComponent(new InputComponent(*this, input));
	AddComponent(new CollisionDetectionComponent<AABBCollider>(*this, new AABBCollider(position_, sprite_.GetWidth(), sprite_.GetHeight()), cm));
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
