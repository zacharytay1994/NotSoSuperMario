#include "Collider.h"

Collider::Collider(D3DXVECTOR2 center, const std::string& type)
	:
	type_(type),
	center_point(center)
{
}

Collider::~Collider()
{
}

bool Collider::DetectCollision(Collider& collider)
{
	return false;
}

AABBCollider::AABBCollider(D3DXVECTOR2 center, const float& width, const float& height)
	:
	Collider(center, "AABB"),
	half_width_(width/2),
	half_height_(height/2)
{
}

AABBCollider::~AABBCollider()
{
}

CircleCollider::CircleCollider(D3DXVECTOR2 center, const float& radius)
	:
	Collider(center, "Circle"),
	radius_(radius)
{
}

CircleCollider::~CircleCollider()
{
}
