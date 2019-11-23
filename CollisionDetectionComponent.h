#pragma once
#include "Component.h"
#include "Collider.h"
#include "GameObject.h"
#include "ColliderManager.h"

template <class T>
class CollisionDetectionComponent : public Component {
private:
	Collider* collider_;
	ColliderManager& collider_manager_;
public:
	CollisionDetectionComponent(GameObject& owner, T* collider, ColliderManager& cm)
		:
		Component(owner),
		collider_(collider),
		collider_manager_(cm)
	{
		collider_manager_.AddCollider(collider_);
	}
	~CollisionDetectionComponent() {
		delete collider_;
		collider_ = nullptr;
	}
	void Update(const float& frametime) override 
	{
		SyncColliderPosition();
		if (CheckForCollision()) {
			owner_.sprite_.GetImage().setScale(0.9f);
		}
		else {
			owner_.sprite_.GetImage().setScale(1.0f);
		}
	}
	void SyncColliderPosition() {
		collider_->center_point.x = owner_.GetPosiiton().x;
		collider_->center_point.y = owner_.GetPosiiton().y;
	}
	bool CheckForCollision() {
		return collider_manager_.QueryCollision(collider_);
	}
	void ExecuteMessage(const Message& msg) override {

	}
};