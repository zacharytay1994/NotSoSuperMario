#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <string>

class Collider {
public:
	std::string type_;
	D3DXVECTOR2 center_point;
public:
	Collider(D3DXVECTOR2 center, const std::string& type);
	virtual ~Collider();
	bool DetectCollision(Collider& collider);
};

class AABBCollider : public Collider {
public:
	float width_;
	float height_;
public:
	AABBCollider(D3DXVECTOR2 center, const std::string& type, const float& width, const float& height);
	~AABBCollider();
};
