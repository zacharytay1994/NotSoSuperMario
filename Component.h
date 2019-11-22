#pragma once

class GameObject;
class Component {
protected:
	GameObject& owner_;
public:
	Component(GameObject& owner);
	virtual ~Component();
	virtual void Update(const float& frametime);
	virtual void Draw();
};