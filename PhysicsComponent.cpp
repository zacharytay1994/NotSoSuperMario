
#include "GameObject.h"
#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent(GameObject& owner): Component(owner, "PhysicsComponent"){
	//velocity = Vec2<float>(0.0f, 0.0f);
	//acceleration = Vec2<float>(0.0f, 0.0f);
	mass = 100.0f;
	inv_mass_ = 1.0f / mass;
	hasGravity = true;
	gravitationalAcceleration = { 0.0f, 980.0f };
}

PhysicsComponent::PhysicsComponent(GameObject& owner, float mass, bool hasGravity=true): Component(owner, "PhysicsComponent") {
	//velocity = Vec2<float>(0.0f, 0.0f);
	//acceleration = Vec2<float>(0.0f, 0.0f);
	this->mass = mass;
	if (mass == 0) {
		inv_mass_ = 0.0f;
	}
	else {
		inv_mass_ = 1.0f / mass;
	}
	this->hasGravity = hasGravity;
	gravitationalAcceleration = { 0.0f, 980.0f };
}

PhysicsComponent::~PhysicsComponent(){
}

void PhysicsComponent::Update(const float& frametime){
	if (hasGravity) {
		ApplyGravity(frametime);
	}
	CalculateVelocity(frametime);
	CalculatePosition(frametime);
	//ApplyLinearDrag(frametime);
	//StayWithinScreen();
}

void PhysicsComponent::Draw(){
	Component::Draw();
}

void PhysicsComponent::CalculatePosition(const float& frametime){
	Vec2<float> velocity2Add = velocity * frametime;
	// consider changing GameObject position to Vec2
	Vec2<float> position = { owner_.GetPosition().x, owner_.GetPosition().y };
	position += velocity2Add;
	// ===TO=REMOVE=========================
	/*if (position.y_ > GAME_HEIGHT) {
		position.y_ = 0;
	}*/
	// =====================================
	owner_.SetPosition(position.x_, position.y_);
}

void PhysicsComponent::CalculateVelocity(const float& frametime){
	velocity += acceleration * frametime;
	if (velocity.x_ < 0.0f) {
		velocity.x_ = velocity.x_ < -max_x_velocity_.x_ ? -max_x_velocity_.x_ : velocity.x_;
	}
	else {
		velocity.x_ = velocity.x_ > max_x_velocity_.y_ ? max_x_velocity_.y_ : velocity.x_;
	}
	if (velocity.y_ < 0.0f) {
		velocity.y_ = velocity.y_ < -max_y_velocity_.x_ ? -max_y_velocity_.x_ : velocity.y_;
	}
	else {
		velocity.y_ = velocity.y_ > max_y_velocity_.y_ ? max_y_velocity_.y_ : velocity.y_;
	}
}

void PhysicsComponent::ApplyForce(Vec2<float> force) {
	acceleration += force / mass;
}

void PhysicsComponent::ApplyGravity(const float& frametime) {
	velocity += gravitationalAcceleration * frametime;
}

void PhysicsComponent::ApplyLinearDrag(const float& frametime)
{
	if (velocity.MagnitudeSq() > 1.0f) {
		velocity = velocity - (velocity.Normalized() * linear_drag_) * frametime;
	}
	else {
		velocity = { 0.0f, 0.0f };
	}
	if (acceleration.MagnitudeSq() > 1.0f) {
		acceleration = acceleration - (acceleration.Normalized() * linear_drag_) * frametime;
	}
	else {
		acceleration = { 0.0f, 0.0f };
	}
}

void PhysicsComponent::SetVelocity(Vec2<float>& vel)
{
	velocity = vel;
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

void PhysicsComponent::AddVelocity(const Vec2<float>& vel)
{
	velocity += vel;
}

Vec2<float> PhysicsComponent::GetVelocity()
{
	return velocity;
}

float PhysicsComponent::GetMass()
{
	return mass;
}

float PhysicsComponent::GetInvMass()
{
	return inv_mass_;
}

float PhysicsComponent::GetRestitution()
{
	return restitution_;
}

void PhysicsComponent::AddPosition(const Vec2<float>& placement)
{
	Vec2<float> original = { owner_.GetPosition().x, owner_.GetPosition().y };
	Vec2<float> added = original + placement;
	owner_.SetPosition(added.x_, added.y_);
}

void PhysicsComponent::StayWithinScreen()
{
	if (owner_.GetPosition().x - owner_.sprite_->GetWidth()/2 < 0.0f) {
		velocity.x_ = abs(velocity.x_);
	}
	if (owner_.GetPosition().x + owner_.sprite_->GetWidth() / 2 > GAME_WIDTH) {
		velocity.x_ = -abs(velocity.x_);
	}
	if (owner_.GetPosition().y - owner_.sprite_->GetHeight()/2  < 0.0f) {
		velocity.y_ = abs(velocity.y_);
	}
	if (owner_.GetPosition().y + owner_.sprite_->GetHeight() / 2 > GAME_HEIGHT) {
		velocity.y_ = -abs(velocity.y_);
	}
}

