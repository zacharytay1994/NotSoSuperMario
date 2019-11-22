#include "Mario.h"
#include "InputComponent.h"

Mario::Mario(Input& input)
	:
	GameObject("pictures\\mariorunsheet.png", 24, 24, 3, D3DXVECTOR2(GAME_WIDTH / 4, GAME_HEIGHT / 4))
{
	sprite_.InitializeAnimation(0, 5, SHIP_ANIMATION_DELAY);
	AddComponent(*(new InputComponent(*this, input)));
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
