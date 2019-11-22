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
	Vec2<float> acceleration = {0.0f, 0.0f};
	float mass;
	bool hasGravity;

	Vec2<float> gravitationalAcceleration = { 0.0f, 98.0f };

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

	void ExecuteMessage(const Message& msg) override;



};