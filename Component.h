#pragma once
#include <iostream> 
#include <vector>


class GameObject;
class Component {
protected:
	GameObject& owner_;
public:	
	enum class ComponentTypes {
		Physics
	};

	struct Message {
		ComponentTypes type_;
		int message_;
		//std::map<std::string, float> params_; // can use vector to improve performance & if we're careful
		std::vector<float> params_;

		Message(ComponentTypes type, int message) {
			type_ = type;
			message_ = message;
		}
		Message(ComponentTypes type, int message, std::vector<float> params) {
			type_ = type;
			message_ = message;
			params_ = params;
		}

	};

	Component(GameObject& owner);
	virtual ~Component();
	virtual void Update(const float& frametime);
	virtual void Draw();

	void ReceiveMessage(const Message& msg);
	virtual void ExecuteMessage(const Message& msg) = 0;
};