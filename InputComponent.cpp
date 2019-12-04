#include "InputComponent.h"
#include "GameObject.h"
#include "PhysicsComponent.h"
#include "Mario.h"

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
	bool input_flag = false;
	if (input_.isKeyDown(SHIP_RIGHT_KEY)) {
		input_flag = true;
		//owner_.SetPosition(owner_.GetPosiiton().x + 1, owner_.GetPosiiton().y);
		/*std::vector<float> params = { 100.0f };
		owner_.TellComponents({ ComponentTypes::Physics, 0, params});*/
		dynamic_cast<PhysicsComponent*>(owner_.GetComponent("PhysicsComponent"))->AddVelocity(Vec2<float>( 1.0f, 0.0f ) * 1200.0f);
		Mario* temp = dynamic_cast<Mario*>(&owner_);
		temp->looking_left = false;
		temp->ChangeSprite(temp->running_animation_);
	}
	if (input_.isKeyDown(SHIP_LEFT_KEY)) {
		input_flag = true;
		//owner_.SetPosition(owner_.GetPosiiton().x - 1, owner_.GetPosiiton().y);
		/*std::vector<float> params = { -100.0f };
		owner_.TellComponents({ ComponentTypes::Physics, 0, params });*/
		dynamic_cast<PhysicsComponent*>(owner_.GetComponent("PhysicsComponent"))->AddVelocity(Vec2<float>(-1.0f, 0.0f) * 1200.0f);
		Mario* temp = dynamic_cast<Mario*>(&owner_);
		temp->looking_left = true;
		temp->ChangeSprite(temp->running_animation_);
	}
	if (input_.isKeyDown(SHIP_UP_KEY) && owner_.on_ground_) {
		input_flag = true;
		/*std::vector<float> params = { -100.0f };
		owner_.TellComponents({ ComponentTypes::Physics, 1, params });*/
		dynamic_cast<PhysicsComponent*>(owner_.GetComponent("PhysicsComponent"))->AddVelocity(Vec2<float>(0.0f, -1.0f) * 30.0f);
	}
	if (input_.wasKeyPressed(SHIP_DOWN_KEY)) {
		input_flag = true;
		/*std::vector<float> params = { 100.0f };
		owner_.TellComponents({ ComponentTypes::Physics, 1, params });*/
	}
	if (!input_flag && owner_.on_ground_) {
		Mario* temp = dynamic_cast<Mario*>(&owner_);
		temp->running_animation_->GetImage().flipHorizontal(false);
		temp->ChangeSprite(temp->hold_);
	}
	else if (!owner_.on_ground_) {
		Mario* temp = dynamic_cast<Mario*>(&owner_);
		temp->running_animation_->GetImage().flipHorizontal(false);
		temp->ChangeSprite(temp->jumping_);
	}
}

void InputComponent::Draw()
{
	Component::Draw();
}

void InputComponent::ExecuteMessage(const Message& msg)
{
}
