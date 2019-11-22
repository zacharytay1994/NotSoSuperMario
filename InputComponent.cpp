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
		//owner_.SetPosition(owner_.GetPosiiton().x + 1, owner_.GetPosiiton().y);
		std::vector<float> params = { 100.0 };
		owner_.TellComponents({ ComponentTypes::Physics, 0, params});
	}
	if (input_.isKeyDown(SHIP_LEFT_KEY)) {
		//owner_.SetPosition(owner_.GetPosiiton().x - 1, owner_.GetPosiiton().y);
		std::vector<float> params = { -100.0 };
		owner_.TellComponents({ ComponentTypes::Physics, 0, params });
	}
	if (input_.isKeyDown(SHIP_UP_KEY)) {
		std::vector<float> params = { -100.0 };
		owner_.TellComponents({ ComponentTypes::Physics, 1, params });
	}
	if (input_.isKeyDown(SHIP_DOWN_KEY)) {
		std::vector<float> params = { 100.0 };
		owner_.TellComponents({ ComponentTypes::Physics, 1, params });
	}
}

void InputComponent::Draw()
{
	Component::Draw();
}

void InputComponent::ExecuteMessage(const Message& msg)
{
}
