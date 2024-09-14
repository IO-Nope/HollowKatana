#pragma once
#ifndef _VECTOR2_H
#define _VECTOR2_H

#include <cmath>

class Vector2
{
public:
	float x = 0;
	float y = 0;

public:
	Vector2() = default;
	~Vector2() = default;

	Vector2(float x, float y) : x(x), y(y) {}

	Vector2 operator+(const Vector2& vec) const
	{
		return Vector2(x + vec.x, y + vec.y);
	}
	void operator+=(const Vector2& vec)
	{
		x += vec.x;
		y += vec.y;
	}
	Vector2 operator-(const Vector2& vec) const
	{
		return Vector2(x - vec.x, y - vec.y);
	}
	void operator-=(const Vector2& vec)
	{
		x -= vec.x;
		y -= vec.y;
	}
	/// <summary>
	/// Êý³Ë
	/// </summary>
	/// <param name="scalar"></param>
	/// <returns></returns>
	//void operator*(float scalar)
	//{
	//	x *= scalar;
	//	y *= scalar;
	//}

	Vector2 operator*(float scalar) {
		return Vector2(x * scalar, y * scalar);
	}
	/// <summary>
	/// ÄÚ»ý
	/// </summary>
	/// <param name="vec"></param>
	/// <returns></returns>
	float operator*(const Vector2& vec) const
	{
		return x * vec.x + y * vec.y;
	}
	Vector2 operator*(const float scalar) const
	{
		return Vector2(x * scalar, y * scalar);
	}
	float length() const
	{
		return sqrt(x * x + y * y);
	}
	Vector2 normalize() const
	{
		float len = length();
		if (len == 0)
		{
			return Vector2(0, 0);
		}
		return Vector2(x / len, y / len);
	}
};
#endif // _VECTOR2_H