#include "Component.h"

Component::Component(GameObject& owner)
	:
	owner_(owner)
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

void Component::ReceiveMessage(const Message& msg){
	ExecuteMessage(msg);
}

