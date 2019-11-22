#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include "Sprite.h"
#include "Component.h"

class GameObject {
private:
	D3DXVECTOR2 position_;
	std::vector<Component*> components_;
public:
	Sprite sprite_;
public:
	GameObject(const std::string& path, const int& width, const int& height, const int& cols, D3DXVECTOR2& pos);
	virtual ~GameObject();
	virtual void Update(const float& frametime);
	virtual void Render();
	void Initialize(Graphics& gfx);
	void AddComponent(Component& component);
	void SyncSprite();

	void SetPosition(const float& x, const float& y);
	D3DXVECTOR2 GetPosiiton();
};