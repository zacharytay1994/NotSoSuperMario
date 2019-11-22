#pragma once
#include "component.h"
#include <d3d9.h>
#include <d3dx9.h>


class GameObject;
class PhysicsComponent : public Component {
private:
	D3DXVECTOR2 velocity = D3DXVECTOR2(0, 0);
	float mass;
	float gravity = 10;

public:
	PhysicsComponent(GameObject& owner);
	~PhysicsComponent();

	void Update(const float& frametime) override;
	void Draw() override;

	void ApplyForce(const D3DXVECTOR2& force, const float& frametime);
	void ApplyGravity(const float& frametime);




};