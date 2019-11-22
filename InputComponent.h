#pragma once
#include "Component.h"
#include "input.h"

class GameObject;
class InputComponent : public Component {
private:
	Input& input_;
public:
	InputComponent(GameObject& owner, Input& input);
	~InputComponent();
	void Update(const float& frametime) override;
	void Draw() override;

	void ExecuteMessage(const Message& msg) override;
};