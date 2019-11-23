#pragma once
#include "Collider.h"

class ColliderManager {
private:
	int max_colliders_ = 128;
	int collider_count_ = 0;
	Collider* collider_array_[128];
public:
	ColliderManager();
	~ColliderManager();
	void AddCollider(Collider* collider);
	bool QueryCollision(Collider* collider);
	// collision checks
	bool AABBvsAABB(const AABBCollider& c1, const AABBCollider& c2);
};