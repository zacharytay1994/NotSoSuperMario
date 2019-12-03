#include "TestObject.h"
#include "CollisionDetectionComponent.h"
#include "PhysicsComponent.h"

TestObject::TestObject(ColliderManager& cm)
	:
	GameObject("pictures\\mariowalls.png", 64, 64, 1, D3DXVECTOR2(GAME_WIDTH - 150, GAME_HEIGHT / 2), "Wall")
{
	AddComponent(new PhysicsComponent(*this));
	AddComponent(new CollisionDetectionComponent<AABBCollider>(*this, new AABBCollider(position_, this, sprite_->GetWidth(), sprite_->GetHeight(), true, true), cm));
}

TestObject::TestObject(ColliderManager& cm, const float& x, const float& y)
	:
	GameObject("pictures\\mariowalls.png", 64, 64, 1, D3DXVECTOR2(x, y))
{
	AddComponent(new PhysicsComponent(*this, 0, false));
	AddComponent(new CollisionDetectionComponent<AABBCollider>(*this, new AABBCollider(position_, this, sprite_->GetWidth(), sprite_->GetHeight(), true, true), cm));
}

TestObject::~TestObject()
{
}

void TestObject::Update(const float& frametime)
{
	GameObject::Update(frametime);
}

void TestObject::Render()
{
	GameObject::Render();
}
