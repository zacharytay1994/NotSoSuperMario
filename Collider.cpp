#include "Collider.h"
#include "GameObject.h"

Collider::Collider(D3DXVECTOR2 center, const std::string& type, GameObject* go, const bool& isstatic, const bool& issimulated)
	:
	type_(type),
	center_point(center),
	owner_(go),
	is_static_(isstatic),
	is_simulated_(issimulated)
{
}

Collider::~Collider()
{
	owner_ = nullptr;
}

bool Collider::DetectCollision(Collider& collider)
{
	return false;
}

AABBCollider::AABBCollider(D3DXVECTOR2 center, GameObject* go, const float& width, const float& height, const bool& isstatic, const bool& issimulated)
	:
	Collider(center, "AABB", go, isstatic, issimulated),
	half_width_(width/2),
	half_height_(height/2)
{
}

AABBCollider::~AABBCollider()
{
}

CircleCollider::CircleCollider(D3DXVECTOR2 center, GameObject* go, const float& radius, const bool& isstatic, const bool& issimulated)
	:
	Collider(center, "Circle", go, isstatic, issimulated),
	radius_(radius)
{
}

CircleCollider::~CircleCollider()
{
}
