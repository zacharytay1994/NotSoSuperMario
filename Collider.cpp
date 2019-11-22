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

AABBCollider::AABBCollider(D3DXVECTOR2 center, const std::string& type, const float& width, const float& height)
	:
	Collider(center, type),
	width_(width),
	height_(height)
{
}

AABBCollider::~AABBCollider()
{
}
