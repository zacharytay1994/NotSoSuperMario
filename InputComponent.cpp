#include "InputComponent.h"
#include "GameObject.h"
#include "PhysicsComponent.h"

InputComponent::InputComponent(GameObject& owner, Input& input)
	:
	Component(owner, "InputComponent"),
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
		/*std::vector<float> params = { 100.0f };
		owner_.TellComponents({ ComponentTypes::Physics, 0, params});*/
		dynamic_cast<PhysicsComponent*>(owner_.GetComponent("PhysicsComponent"))->AddVelocity(Vec2<float>( 1.0f, 0.0f ) * 3.0f);
	}
	if (input_.isKeyDown(SHIP_LEFT_KEY)) {
		//owner_.SetPosition(owner_.GetPosiiton().x - 1, owner_.GetPosiiton().y);
		/*std::vector<float> params = { -100.0f };
		owner_.TellComponents({ ComponentTypes::Physics, 0, params });*/
		dynamic_cast<PhysicsComponent*>(owner_.GetComponent("PhysicsComponent"))->AddVelocity(Vec2<float>(-1.0f, 0.0f) * 3.0f);
	}
	if (input_.isKeyDown(SHIP_UP_KEY)) {
		/*std::vector<float> params = { -100.0f };
		owner_.TellComponents({ ComponentTypes::Physics, 1, params });*/
		dynamic_cast<PhysicsComponent*>(owner_.GetComponent("PhysicsComponent"))->AddVelocity(Vec2<float>(0.0f, -1.0f) * 20.0f);
	}
	if (input_.isKeyDown(SHIP_DOWN_KEY)) {
		/*std::vector<float> params = { 100.0f };
		owner_.TellComponents({ ComponentTypes::Physics, 1, params });*/
		//dynamic_cast<PhysicsComponent*>(owner_.GetComponent("PhysicsComponent"))->AddVelocity(Vec2<float>(0.0f, 1.0f) * 20.0f);
	}
}

void InputComponent::Draw()
{
	Component::Draw();
}

void InputComponent::ExecuteMessage(const Message& msg)
{
}
