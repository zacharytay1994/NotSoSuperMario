#include "ColliderManager.h"
#include "GameObject.h"
#include "PhysicsComponent.h"

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
	if (collider->owner_->removed_) {
		return false;
	}
	// reset touch
	collider->owner_->touch_.touch_top_ = false;
	collider->owner_->touch_.touch_bottom_ = false;
	collider->owner_->touch_.touch_left_ = false;
	collider->owner_->touch_.touch_right_ = false;
	// not the static bodies job to resolve
	if (collider->is_static_ && !collider->is_static_check_ || collider->owner_->removed_) {
		return false;
	}
	// determine this collider type
	if (collider->type_ == "AABB") {
		for each (Collider * c in collider_array_) {
			/*if (collider->resolved_) {
				collider->resolved_ = false;
				return true;
			}*/
			if (c != nullptr) {
				// determine if not self
				if (c != collider) {
					if (c->owner_->removed_) {
						continue;
					}
					// determine other collider type
					if (c->type_ == "AABB") {
						if (AABBvsAABB(*dynamic_cast<AABBCollider*>(collider), *dynamic_cast<AABBCollider*>(c))) {
							//collider->resolved_ = true;
							// if this and other collider is simulated, resolve collision
							if (collider->is_simulated_ && c->is_simulated_) {
								// generate manifold
								CollisionManifold manifold = AABBvsAABBManifold(*dynamic_cast<AABBCollider*>(collider), *dynamic_cast<AABBCollider*>(c));
								// temp solution ------------------------------------
								// if collision normal downwards detected
								if (manifold.collision_normal_.y_ == 1) {
									collider->owner_->touch_.touch_bottom_ = true;
									collider->owner_->touch_obj_.touch_obj_bottom_ = c;
									if (!c->is_static_) {
										collider->owner_->bounce_off_others_ = true;
									}
								}
								if (manifold.collision_normal_.y_ == -1) {
									collider->owner_->touch_.touch_top_ = true;
									collider->owner_->touch_obj_.touch_obj_top_ = c;
								}
								if (manifold.collision_normal_.x_ == 1) {
									collider->owner_->touch_.touch_left_ = true;
									collider->owner_->touch_obj_.touch_obj_left_ = c;
								}
								if (manifold.collision_normal_.x_ == -1) {
									collider->owner_->touch_.touch_right_ = true;
									collider->owner_->touch_obj_.touch_obj_right_ = c;
								}
								// --------------------------------------------------
								ForceCorrect(manifold);
								ResolveCollision(manifold);
								CalculateFriction(manifold);
								return true;
							}
							// otherwise, check for but don't resolve collision
							else {
								// generate manifold
								CollisionManifold manifold = AABBvsAABBManifold(*dynamic_cast<AABBCollider*>(collider), *dynamic_cast<AABBCollider*>(c));
								// temp solution ------------------------------------
								// if collision normal downwards detected
								if (manifold.collision_normal_.y_ == 1) {
									collider->owner_->touch_.touch_bottom_ = true;
									collider->owner_->touch_obj_.touch_obj_bottom_ = c;
								}
								if (manifold.collision_normal_.y_ == -1) {
									collider->owner_->touch_.touch_top_ = true;
									collider->owner_->touch_obj_.touch_obj_top_ = c;
								}
								if (manifold.collision_normal_.x_ == 1) {
									collider->owner_->touch_.touch_left_ = true;
									collider->owner_->touch_obj_.touch_obj_left_ = c;
								}
								if (manifold.collision_normal_.x_ == -1) {
									collider->owner_->touch_.touch_right_ = true;
									collider->owner_->touch_obj_.touch_obj_right_ = c;
								}
								// --------------------------------------------------
								return true;
							}
						}
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

CollisionManifold ColliderManager::AABBvsAABBManifold(AABBCollider& c1, AABBCollider& c2)
{
	CollisionManifold manifold;
	// get object of each collider
	manifold.A = c1.owner_;
	manifold.B = c2.owner_;

	// get penetration
	float x_penetration;
	float y_penetration;
	if (c1.center_point.x < c2.center_point.x) {
		x_penetration = (c1.center_point.x + c1.half_width_) - (c2.center_point.x - c2.half_width_);
	}
	else {
		x_penetration = (c2.center_point.x + c2.half_width_) - (c1.center_point.x - c1.half_width_);
	}
	if (c1.center_point.y < c2.center_point.y) {
		y_penetration = (c1.center_point.y + c1.half_height_) - (c2.center_point.y - c2.half_height_);
	}
	else {
		y_penetration = (c2.center_point.y + c2.half_height_) - (c1.center_point.y - c1.half_height_);
	}
	

	// set manifold to lowest penetration
	if (x_penetration < y_penetration) {
		manifold.penetration_depth_ = x_penetration;
		if (c1.center_point.x < c2.center_point.x) {
			manifold.collision_normal_ = { 1,0 };
		}
		else {
			manifold.collision_normal_ = { -1,0 };
		}
	}
	else {
		manifold.penetration_depth_ = y_penetration;
		if (c1.center_point.y < c2.center_point.y) {
			manifold.collision_normal_ = { 0,1 };
		}
		else {
			manifold.collision_normal_ = { 0,-1 };
		}
	}
	return manifold;
}

void ColliderManager::ResolveCollision(CollisionManifold& m)
{
	PhysicsComponent* A = dynamic_cast<PhysicsComponent*>(m.A->GetComponent("PhysicsComponent"));
	PhysicsComponent* B = dynamic_cast<PhysicsComponent*>(m.B->GetComponent("PhysicsComponent"));
	// calculate relative velocity
	Vec2<float> relative_velocity = B->GetVelocity() - A->GetVelocity();

	// calculate relative velocity in terms of normal direction
	float velocity_along_normal = relative_velocity * m.collision_normal_;

	// if velocities are seperating do nothing
	if (velocity_along_normal > 0) {
		return;
	}

	// get lowest restitution
	float lowest_restitution = A->GetRestitution() < B->GetRestitution() ? A->GetRestitution() : B->GetRestitution();

	// calculate impulse scalar
	float j = velocity_along_normal * (-(1 + lowest_restitution));
	j /= A->GetInvMass() + B->GetInvMass();

	// apply impulse
	Vec2<float> impulse = m.collision_normal_ * j;
	A->AddVelocity(-impulse * A->GetInvMass());
	B->AddVelocity(impulse * B->GetInvMass());

}

void ColliderManager::CalculateFriction(CollisionManifold& m)
{
	// only apply friction on up and down surface
	if (m.collision_normal_.x_ != 0) {
		return;
	}
	PhysicsComponent* A = dynamic_cast<PhysicsComponent*>(m.A->GetComponent("PhysicsComponent"));
	PhysicsComponent* B = dynamic_cast<PhysicsComponent*>(m.B->GetComponent("PhysicsComponent"));
	// calculate relative velocity
	Vec2<float> relative_velocity = B->GetVelocity() - A->GetVelocity();

	// calculate tangent vector
	Vec2<float> tangent = (relative_velocity - (m.collision_normal_ * (relative_velocity * m.collision_normal_))).Normalized();

	// solve for magnitude to apply along friction vector
	float jt = -(relative_velocity * tangent);
	jt = jt / (A->GetInvMass() + B->GetInvMass());
	Vec2<float> friction_impulse = tangent * jt;

	float friction_coefficient = 0.8f;
	// need some fixing here ---- future ----
	A->AddVelocity(-friction_impulse * A->GetInvMass() * friction_coefficient);
	B->AddVelocity(friction_impulse * B->GetInvMass() * friction_coefficient);
}

void ColliderManager::CorrectPosition(CollisionManifold& m)
{
	PhysicsComponent* A = dynamic_cast<PhysicsComponent*>(m.A->GetComponent("PhysicsComponent"));
	PhysicsComponent* B = dynamic_cast<PhysicsComponent*>(m.B->GetComponent("PhysicsComponent"));
	float percent = 0.8f;
	float slop = 0.01f;
	Vec2<float> correction = m.collision_normal_ * (max(m.penetration_depth_ - slop, 0.0f) / (A->GetInvMass() + B->GetInvMass()) * percent);
	A->AddPosition(-correction * A->GetInvMass());
	B->AddPosition(correction * B->GetInvMass());
}

void ColliderManager::ForceCorrect(CollisionManifold& m)
{
	float buffer = 0.1f;
	PhysicsComponent* A = dynamic_cast<PhysicsComponent*>(m.A->GetComponent("PhysicsComponent"));
	PhysicsComponent* B = dynamic_cast<PhysicsComponent*>(m.B->GetComponent("PhysicsComponent"));
	// if horizontal collision apply more force correct
	if (m.collision_normal_.x_ != 0) {
		A->AddPosition(m.collision_normal_ * (-m.penetration_depth_ - 1.0f));
	}
	else {
		A->AddPosition(m.collision_normal_ * (-m.penetration_depth_ - buffer));
	}
	//A->AddPosition(m.collision_normal_ * (-m.penetration_depth_ - buffer));
}
