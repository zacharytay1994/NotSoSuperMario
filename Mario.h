#pragma once

#include "GameObject.h"

class Input;
class Mario : public GameObject {
private:
public:
	Mario(Input& input);
	~Mario();
	void Update(const float& frametime) override;
	void Render() override;
};