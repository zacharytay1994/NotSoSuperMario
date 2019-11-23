#include "ColliderManager.h"

ColliderManager::ColliderManager()
	:
	collider_array_()
{
}

ColliderManager::~ColliderManager()
{
	/*for each (Collider * c in collider_array_) {
		if (c != nullptr) {
			delete c;
			c = nullptr;
		}
	}*/
}

void ColliderManager::AddCollider(Collider* collider)
{
	if (collider_count_ < max_colliders_) {
		collider_array_[collider_count_] = collider;
		collider_count_++;
	}
}

bool ColliderManager::QueryCollision(Collider* collider)
{
	// determine this collider type
	if (collider->type_ == "AABB") {
		for each (Collider * c in collider_array_) {
			if (c != nullptr) {
				// determine if not self
				if (c != collider) {
					// determine other collider type
					if (c->type_ == "AABB") {
						return AABBvsAABB(*dynamic_cast<AABBCollider*>(collider), *dynamic_cast<AABBCollider*>(c));
					}
				}
			}
		}
	}
	return false;
}

bool ColliderManager::AABBvsAABB(const AABBCollider& c1, const AABBCollider& c2)
{
	float c1_left = c1.center_point.x - c1.half_width_;
	float c1_right = c1.center_point.x + c1.half_width_;
	float c1_top = c1.center_point.y - c1.half_height_;
	float c1_bottom = c1.center_point.y + c1.half_height_;

	float c2_left = c2.center_point.x - c2.half_width_;
	float c2_right = c2.center_point.x + c2.half_width_;
	float c2_top = c2.center_point.y - c2.half_height_;
	float c2_bottom = c2.center_point.y + c2.half_height_;
	return !(c1_left > c2_right || c1_right < c2_left || c1_top > c2_bottom || c1_bottom < c2_top);
}
