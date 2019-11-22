#include "InputComponent.h"
#include "GameObject.h"

InputComponent::InputComponent(GameObject& owner, Input& input)
	:
	Component(owner),
	input_(input)
{
}

InputComponent::~InputComponent()
{
}

void InputComponent::Update(const float& frametime)
{
	Component::Update(frametime);
	if (input_.isKeyDown(SHIP_RIGHT_KEY)) {
		owner_.SetPosition(owner_.GetPosiiton().x + 1, owner_.GetPosiiton().y);
	}
	if (input_.isKeyDown(SHIP_LEFT_KEY)) {
		owner_.SetPosition(owner_.GetPosiiton().x - 1, owner_.GetPosiiton().y);
	}
	if (input_.isKeyDown(SHIP_UP_KEY)) {
		owner_.SetPosition(owner_.GetPosiiton().x, owner_.GetPosiiton().y - 1);
	}
	if (input_.isKeyDown(SHIP_DOWN_KEY)) {
		owner_.SetPosition(owner_.GetPosiiton().x, owner_.GetPosiiton().y + 1);
	}
}

void InputComponent::Draw()
{
	Component::Draw();
}
