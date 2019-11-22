#pragma once
#include "Component.h"

class Collider;
class CollisionDetection : public Component {
private:
	Collider* collider_;
public:
	CollisionDetection();
	~CollisionDetection();
};