#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Sprite.h"

class GameObject {
private:
	D3DXVECTOR2 position_;
	Sprite sprite_;
public:
	GameObject(const std::string& path, const int& width, const int& height, const int& cols, D3DXVECTOR2& pos);
	~GameObject();
	void Update();
	void Render();
	void Initialize(Graphics& gfx);
};