#pragma once
#include "Component.h"
#include "input.h"

#include <string>
#include <sstream>

class GameObject;
class InputComponent : public Component {
private:
	Input& input_;
	std::stringstream ss;
public:
	InputComponent(GameObject& owner, Input& input);
	~InputComponent();
	void Update(const float& frametime) override;
	void Draw() override;

	void ExecuteMessage(const Message& msg) override;
};