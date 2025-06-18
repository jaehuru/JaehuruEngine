#pragma once
#include <cmath>
#include <functional>

namespace huru::math
{
    constexpr float PI = 3.14159265359f;

    static float ConvertDegree(float radian)
    {
        return radian * (180.0f / PI);
    }

    struct Vector2
    {
        float x;
        float y;

        Vector2() : x(0.0f), y(0.0f) {}
        Vector2(float _x, float _y) : x(_x), y(_y) {}

        // 정적 멤버 함수
        static Vector2 Rotate(const Vector2& vector, float degree)
        {
            float radian = (degree / 180.f) * PI;
            Vector2 norm = vector.normalize();
            float x = cosf(radian) * norm.x - sinf(radian) * norm.y;
            float y = sinf(radian) * norm.x + cosf(radian) * norm.y;
            return Vector2(x, y);
        }

        static float Dot(const Vector2& v1, const Vector2& v2)
        {
            return v1.x * v2.x + v1.y * v2.y;
        }

        static float Cross(const Vector2& v1, const Vector2& v2)
        {
            return v1.x * v2.y - v1.y * v2.x;
        }

        static Vector2 Lerp(const Vector2& start, const Vector2& end, float t)
        {
            return start * (1.0f - t) + end * t;
        }

        // 연산자 오버로딩
        Vector2 operator-() const { return Vector2(-x, -y); }
        Vector2 operator+(const Vector2& other) const { return Vector2(x + other.x, y + other.y); }
        Vector2& operator+=(const Vector2& other)
        {
            x += other.x; y += other.y;
            return *this;
        }
        Vector2& operator-=(const Vector2& other)
        {
            x -= other.x; y -= other.y;
            return *this;
        }
        Vector2& operator*=(const Vector2& other)
        {
            x *= other.x; y *= other.y;
            return *this;
        }
        Vector2& operator*=(float value)
        {
            x *= value; y *= value;
            return *this;
        }
        Vector2& operator/=(const Vector2& other)
        {
            x /= other.x; y /= other.y;
            return *this;
        }
        Vector2 operator-(const Vector2& other) const { return Vector2(x - other.x, y - other.y); }
        Vector2 operator/(float value) const { return Vector2(x / value, y / value); }
        Vector2 operator*(float value) const { return Vector2(x * value, y * value); }
        Vector2 operator*(const Vector2& v) const { return Vector2(x * v.x, y * v.y); }
        bool operator==(const Vector2& v) const { return (x == v.x) && (y == v.y); }

        // 멤버 함수
        void clear()
        {
            x = 0.f; y = 0.f;
        }

        float length() const
        {
            return sqrtf(x * x + y * y);
        }

        Vector2 normalize() const
        {
            float len = length();
            if (len == 0.f)
                return Vector2(0.f, 0.f);
            return Vector2(x / len, y / len);
        }

        // 정적 멤버 변수 선언
        static Vector2 One;
        static Vector2 Zero;
        static Vector2 Right;
        static Vector2 Left;
        static Vector2 Up;
        static Vector2 Down;
    };
}
