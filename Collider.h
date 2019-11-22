#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <string>

class Collider {
public:
	std::string type_;
	D3DXVECTOR2 center_point;
public:
	Collider() = default;
	Collider(D3DXVECTOR2 center, const std::string& type);
	virtual ~Collider();
	bool DetectCollision(Collider& collider);
};

class AABBCollider : public Collider {
public:
	float half_width_;
	float half_height_;
public:
	AABBCollider(D3DXVECTOR2 center, const float& width, const float& height);
	~AABBCollider();
};

class CircleCollider : public Collider {
public:
	float radius_;
public:
	CircleCollider(D3DXVECTOR2 center, const float& radius);
	~CircleCollider();
};
