#pragma once
#include "GameObject.h"

class MarioGhost: public GameObject {
private:
public:
	MarioGhost();
	~MarioGhost();
	void Update(const float& frametime) override;
	void Render() override;
};