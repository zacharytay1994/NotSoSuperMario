#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <string>

class GameObject;
class Collider {
public:
	std::string type_;
	D3DXVECTOR2 center_point;
	GameObject* owner_;
	bool is_static_ = false; // meaning infinite mass
	bool is_simulated_ = true; // meaning collider body is to be resolved
	bool resolved_ = false;
public:
	Collider() = default;
	Collider(D3DXVECTOR2 center, const std::string& type, GameObject* go, const bool& isstatic, const bool& issimulated);
	virtual ~Collider();
	bool DetectCollision(Collider& collider);
};

class AABBCollider : public Collider {
public:
	float half_width_;
	float half_height_;
public:
	AABBCollider(D3DXVECTOR2 center, GameObject* go, const float& width, const float& height, const bool& isstatic, const bool& issimulated);
	~AABBCollider();
};

class CircleCollider : public Collider {
public:
	float radius_;
public:
	CircleCollider(D3DXVECTOR2 center, GameObject* go, const float& radius, const bool& isstatic, const bool& issimulated);
	~CircleCollider();
};
