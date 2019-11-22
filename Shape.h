#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <string>

struct Shape {
	D3DXVECTOR2 center_point_;
	std::string type_;
	Shape(const D3DXVECTOR2& center, const std::string& type) {
		center_point_ = center;
		type_ = type;
	}
};

struct Circle : public Shape {
	float radius_;
	Circle(const D3DXVECTOR2& center, const float& radius)
		:
		Shape(center, "circle")
	{
		radius_ = radius;
	}
};

struct AABB : public Shape {
	float width_;
	float height_;
	AABB(const D3DXVECTOR2& center, const float& width, const float& height) 
		:
		Shape(center, "AABB")
	{
		width_ = width;
		height_ = height;
	}
};