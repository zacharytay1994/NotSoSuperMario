#pragma once
#include "component.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "Vec2.h"


class GameObject;
class PhysicsComponent : public Component {
private:
	ComponentTypes type_ = ComponentTypes::Physics;

	Vec2<float> velocity = {0.0f, 0.0f};
	Vec2<float> max_x_velocity_ = { 200.0f, 200.0f };
	Vec2<float> max_y_velocity_ = { 400.0f, 1000.0f };
	Vec2<float> acceleration = {0.0f, 0.0f};
	float mass;
	float inv_mass_;
	float restitution_ = 0.2f;
	float linear_drag_ = 10.0f;
	bool hasGravity;

	float max_acceleration_ = 10.0f;

	Vec2<float> gravitationalAcceleration = { 0.0f, 980.0f };

	// Update postion by adding velocity to position
	void CalculatePosition(const float& frametime);

	// Update velocity by adding acceeration to velocity
	void CalculateVelocity(const float& frametime);

public:
	// constructor
	PhysicsComponent(GameObject& owner);
	// constructor with mass & gravity
	PhysicsComponent(GameObject& owner, float mass, bool hasGravity);
	// destructor
	~PhysicsComponent();
	void Update(const float& frametime) override;
	void Draw() override;
	void ApplyForce(Vec2<float> force);
	void ApplyGravity(const float& frametime);
	void ApplyLinearDrag(const float& frametime);
	void SetVelocity(Vec2<float>& vel);
	void ExecuteMessage(const Message& msg) override;

	void AddVelocity(const Vec2<float>& velocity);
	Vec2<float> GetVelocity();
	float GetMass();
	float GetInvMass();
	float GetRestitution();
	void AddPosition(const Vec2<float>& placement);
	void StayWithinScreen();
};