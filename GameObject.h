#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <string>
#include "Sprite.h"
#include "Component.h"

class Collider;
struct TouchData {
	bool touch_bottom_;
	bool touch_top_;
	bool touch_right_;
	bool touch_left_;
};
struct TouchObject {
	Collider* touch_obj_bottom_;
	Collider* touch_obj_top_;
	Collider* touch_obj_right_;
	Collider* touch_obj_left_;
};
class GameObject {
protected:
	D3DXVECTOR2 position_;
	std::vector<Component*> components_;
public:
	Sprite* sprite_;
	Sprite* hold_;
	// temporary fix
	TouchData touch_ = { false, false, false, false };
	TouchObject touch_obj_ = { NULL, NULL, NULL, NULL };
	bool on_ground_ = false;
	float air_time_ = 0.0f;
	// "hacky fixes"
	float death_timer_ = 0.5f;
	bool pend_removal_ = false;
	bool removed_ = false;
	bool bounce_off_others_ = false;
	float bounce_strength_ = 300.0f;
	std::string type_ = "";
public:
	GameObject(const std::string& path, const int& width, const int& height, const int& cols, D3DXVECTOR2& pos, std::string t = "");
	virtual ~GameObject();
	virtual void Update(const float& frametime);
	virtual void Render();
	void Initialize(Graphics& gfx);
	virtual void ChildInitialize(Graphics& gfx);
	void AddComponent(Component* component);
	Component* GetComponent(std::string type);
	void SyncSprite();
	void ChangeSprite(Sprite* sprite);
	void ProcessOnGround(const float& frametime);

	void SetPosition(const float& x, const float& y);
	D3DXVECTOR2 GetPosition();

	void TellComponents(Component::Message msg);

	void PendRemoval(const float& frametime);
};