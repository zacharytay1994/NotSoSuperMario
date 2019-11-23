#pragma once

template <class T>
class Vec2 {
public:
	T x_;
	T y_;
public:
	Vec2() = default;

	Vec2(T x, T y)
		:
		x_(x),
		y_(y)
	{}
	Vec2& operator=(const Vec2& rhs) {
		x_ = rhs.x_;
		y_ = rhs.y_;
		return *this;
	}
	Vec2& operator+=(const Vec2& rhs) {
		x_ += rhs.x_;
		y_ += rhs.y_;
		return *this;
	}
	Vec2 operator+(const Vec2& rhs) {
		return { x_ + rhs.x_, y_ + rhs.y_ };
	}
	Vec2& operator*=(const float& val) {
		x_ *= val;
		y_ *= val;
		return *this;
	}
	Vec2 operator*(const float& val) {
		return { x_ * val, y_ * val };
	}
	float operator*(const Vec2& vec) {
		return x_ * vec.x_ + y_ * vec.y_;
	}
	Vec2 operator/ (const float& val) {
		return { x_ / val, y_ / val };
	}
	Vec2& operator-=(const Vec2& rhs) {
		x_ -= rhs.x_;
		y_ -= rhs.y_;
		return *this;
	}
	Vec2 operator-(const Vec2& rhs) {
		return { x_ - rhs.x_, y_ - rhs.y_ };
	}
	float Magnitude() {
		return sqrt(x_ * x_ + y_ * y_);
	}
	Vec2 Normalized() {
		if (this->Magnitude() == 0.0f) {
			return { 0.0f, 0.0f };
		}
		return (*this / this->Magnitude());
	}
	float MagnitudeSq() {
		return x_ * x_ + y_ * y_;
	}
	Vec2& operator-() {
		x_ = -x_;
		y_ = -y_;
		return *this;
	}
};