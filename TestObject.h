#pragma once

#include "GameObject.h"

class Input;
class ColliderManager;
class TestObject : public GameObject {
private:
public:
	TestObject(ColliderManager& cm);
	TestObject(ColliderManager& cm, const float& x, const float& y);
	~TestObject();
	void Update(const float& frametime) override;
	void Render() override;
};