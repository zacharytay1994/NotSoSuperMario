#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <string>
#include "Sprite.h"
#include "Component.h"

class GameObject {
protected:
	D3DXVECTOR2 position_;
	std::vector<Component*> components_;
public:
	Sprite* sprite_;
	Sprite* hold_;
	// temporary fix
	bool touched_ground_ = false;
	bool on_ground_ = false;
	float air_time_ = 0.0f;
public:
	GameObject(const std::string& path, const int& width, const int& height, const int& cols, D3DXVECTOR2& pos);
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
};