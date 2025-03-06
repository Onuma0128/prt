#pragma once
#include <cmath>
#include <math.h>

struct Vector2 {
	float x;
	float y;

	// + 演算子のオーバーロード
	Vector2 operator+(const Vector2& other) const {
		return Vector2{ x + other.x, y + other.y };
	}
	// - 演算子のオーバーロード
	Vector2 operator+(float other) const {
		return Vector2{ x + other, y + other };
	}

	// - 演算子のオーバーロード
	Vector2 operator-(const Vector2& other) const {
		return Vector2{ x - other.x, y - other.y };
	}
	// - 演算子のオーバーロード
	Vector2 operator-(float other) const {
		return Vector2{ x - other, y - other };
	}

	// * 演算子のオーバーロード
	Vector2 operator*(const Vector2& other) const {
		return Vector2{ x * other.x, y * other.y };
	}
	// * 演算子のオーバーロード
	Vector2 operator*(float other) const {
		return Vector2{ x * other, y * other };
	}
	// * 演算子のオーバーロード
	Vector2 operator/(const Vector2& other) const {
		return Vector2{ x / other.x, y / other.y };
	}
	// * 演算子のオーバーロード
	Vector2 operator/(float other) const {
		return Vector2{ x / other, y / other };
	}
	// + 演算子のオーバーロード
	Vector2& operator+=(const Vector2& other) {

		x += other.x;
		y += other.y;
		return *this;
	}
	// + 演算子のオーバーロード
	Vector2& operator-=(const Vector2& other) {

		x -= other.x;
		y -= other.y;
		return *this;
	}
	// 長さ
	float Length() {
		float result;

		result = sqrtf((x * x) + (y * y));

		return result;
	};
};
static Vector2 Normalize(const Vector2& v) {
	Vector2 result{};
	float length;

	length = sqrtf((v.x * v.x) + (v.y * v.y));

	if (length != 0.0f) {
		result.x = v.x / length;
		result.y = v.y / length;
	};

	return result;
};
static float Length(const Vector2& v) {
	float result;

	result = sqrtf((v.x * v.x) + (v.y * v.y));

	return result;
};

static Vector2 Lerp(const Vector2& v1, const Vector2& v2, float t) {
	return Vector2{
		v1.x + (v2.x - v1.x) * t,
		v1.y + (v2.y - v1.y) * t
	};
}
