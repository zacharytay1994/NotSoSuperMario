#include "TestObject.h"
#include "CollisionDetectionComponent.h"

TestObject::TestObject(ColliderManager& cm)
	:
	GameObject("pictures\\testsquare.png", 128, 128, 1, D3DXVECTOR2(GAME_WIDTH - 150, GAME_HEIGHT / 2))
{
	AddComponent(new CollisionDetectionComponent<AABBCollider>(*this, new AABBCollider(position_, sprite_.GetWidth(), sprite_.GetHeight()), cm));
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
