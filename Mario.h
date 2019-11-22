#pragma once

#include "GameObject.h"

class Input;
class ColliderManager;
class Mario : public GameObject {
private:
public:
	Mario(Input& input, ColliderManager& cm);
	~Mario();
	void Update(const float& frametime) override;
	void Render() override;
};