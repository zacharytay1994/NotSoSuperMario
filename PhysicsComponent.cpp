
#include "GameObject.h"
#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent(GameObject& owner): Component(owner){
}

PhysicsComponent::~PhysicsComponent(){
}

void PhysicsComponent::Update(const float& frametime){
	Component::Update(frametime);

	D3DXVECTOR2 actualVelocity;
	D3DXVec2Scale(&actualVelocity, &velocity, frametime);
	D3DXVECTOR2 position = owner_.GetPositon();
	D3DXVec2Add()
}

void PhysicsComponent::Draw(){
	Component::Draw();
}

void PhysicsComponent::ApplyForce(const D3DXVECTOR2& force, const float& frametime){
}

void PhysicsComponent::ApplyGravity(const float& frametime){
}
