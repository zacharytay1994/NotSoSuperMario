#pragma once
#include "Collider.h"
#include "Vec2.h"

struct CollisionManifold {
	GameObject* A;
	GameObject* B;
	Vec2<float> collision_normal_;
	float penetration_depth_;
};
class ColliderManager {
private:
	int max_colliders_ = 1000;
	int collider_count_ = 0;
	Collider* collider_array_[1000];
public:
	ColliderManager();
	~ColliderManager();
	void AddCollider(Collider* collider);
	bool QueryCollision(Collider* collider);
	// collision checks
	bool AABBvsAABB(const AABBCollider& c1, const AABBCollider& c2);
	// manifold generation
	CollisionManifold AABBvsAABBManifold(AABBCollider& c1, AABBCollider& c2);
	void ResolveCollision(CollisionManifold& m);
	void CalculateFriction(CollisionManifold& m);
	void CorrectPosition(CollisionManifold& m);
	void ForceCorrect(CollisionManifold& m);
};