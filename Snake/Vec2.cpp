#include "Vec2.hpp"
#include <iostream>
#include <string>

#include <cmath>
Vec2::Vec2()
{
}

Vec2::Vec2(float xin, float yin)
	: x(xin)
	, y(yin)
{
}

bool Vec2::operator==(const Vec2& rhs) const
{
	return (x == rhs.x && y == rhs.y);
}

bool Vec2::operator>=(const Vec2 rhs) const
{
	return (x >= rhs.x || y >= rhs.y);
}

bool Vec2::operator<=(const Vec2 rhs) const
{
	return (x <= rhs.x || y <= rhs.y);
}

bool Vec2::operator!=(const Vec2& rhs) const
{
	return !(operator==(rhs));
}

Vec2 Vec2::operator+(const Vec2& rhs) const
{
	return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator-(const Vec2& rhs) const
{
	return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator/(const float val) const
{
	return Vec2(x / val, y / val);
}

Vec2 Vec2::operator*(const float val) const
{
	return Vec2(x * val, y * val);
}

Vec2 Vec2::operator/(const Vec2& rhs) const
{
	return Vec2(x / rhs.x, y / rhs.y);
}

Vec2 Vec2::operator*(const Vec2& rhs) const
{
	return Vec2(x * rhs.x, y * rhs.y);
}

void Vec2::operator+=(const Vec2& rhs)
{
	x += rhs.x;
	y += rhs.y;
}

void Vec2::operator-=(const Vec2& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
}

void Vec2::operator*=(const float val)
{
	x *= val;
	y *= val;
}

void Vec2::operator/=(const float val)
{
	x /= val;
	y /= val;
}


float Vec2::dist(const Vec2& rhs) const
{
	return sqrt(pow(x - rhs.x, 2) + pow(y - rhs.y, 2));
}

float Vec2::length() const
{
	return sqrt(x * x + y * y);
}

void Vec2::normalize()
{
	float len = length();
	(*this) /= len;
}

const Vec2& Vec2::randomVec(const int _x, const int _y)
{
	int x = std::rand() % _x;
	int y = std::rand() % _y;
	return Vec2(x, y);
}


