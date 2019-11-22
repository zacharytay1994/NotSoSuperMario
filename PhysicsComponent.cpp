
#include "GameObject.h"
#include "PhysicsComponent.h"




PhysicsComponent::PhysicsComponent(GameObject& owner): Component(owner){
	//velocity = Vec2<float>(0.0f, 0.0f);
	//acceleration = Vec2<float>(0.0f, 0.0f);
	mass = 100;
	hasGravity = true;
}

PhysicsComponent::PhysicsComponent(GameObject& owner, float mass, bool hasGravity=true): Component(owner) {
	//velocity = Vec2<float>(0.0f, 0.0f);
	//acceleration = Vec2<float>(0.0f, 0.0f);
	this->mass = mass;
	this->hasGravity = hasGravity;
}

PhysicsComponent::~PhysicsComponent(){
}

void PhysicsComponent::Update(const float& frametime){
	if (hasGravity) {
		ApplyGravity(frametime);
	}
	CalculateVelocity(frametime);
	CalculatePosition(frametime);
}

void PhysicsComponent::Draw(){
	Component::Draw();
}

void PhysicsComponent::CalculatePosition(const float& frametime){
	Vec2<float> velocity2Add = velocity * frametime;
	// consider changing GameObject position to Vec2
	Vec2<float> position = { owner_.GetPosiiton().x, owner_.GetPosiiton().y };
	position += velocity2Add;
	// ===TO=REMOVE=========================
	if (position.y_ > GAME_HEIGHT) {
		position.y_ = 0;
	}
	// =====================================
	owner_.SetPosition(position.x_, position.y_);
}

void PhysicsComponent::CalculateVelocity(const float& frametime){
	velocity += acceleration * frametime;
}

void PhysicsComponent::ApplyForce(Vec2<float> force) {
	acceleration += force / mass;
}

void PhysicsComponent::ApplyGravity(const float& frametime) {
	velocity += gravitationalAcceleration * frametime;
}

void PhysicsComponent::ExecuteMessage(const Message& msg){
	switch (msg.type_) {
	case ComponentTypes::Physics:


		if (msg.message_==0) {
			ApplyForce({ msg.params_[0] , 0 });
		} else if (msg.message_ == 1) {
			ApplyForce({ 0, msg.params_[0]});
		}

		
		break;
	}
}

