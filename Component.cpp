#include "Component.h"

Component::Component(GameObject& owner, const std::string& type)
	:
	owner_(owner),
	type_(type)
{
}

Component::~Component()
{
}

void Component::Update(const float& frametime)
{
}

void Component::Draw()
{
}

std::string Component::GetType()
{
	return type_;
}

void Component::ReceiveMessage(const Message& msg){
	ExecuteMessage(msg);
}

