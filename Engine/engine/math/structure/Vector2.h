#pragma once
#include <math.h>
#include <cmath>

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

    // 複合代入演算子オーバーロード
    Vector2 operator+=(const Vector2& v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    Vector2 operator-=(const Vector2& v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    Vector2 operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }


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