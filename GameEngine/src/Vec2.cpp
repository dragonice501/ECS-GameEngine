#include "Vec2.h"
#include <math.h>
#include <iostream>

Vec2& Vec2::operator = (const Vec2& v) {
	x = v.x;
	y = v.y;
	return *this;
}

bool Vec2::operator == (const Vec2& v) const {
	return x == v.x && y == v.y;
}

bool Vec2::operator != (const Vec2& v) const {
	return !(*this == v);
}

Vec2 Vec2::operator + (const Vec2& v) const {
	Vec2 result;
	result.x = x + v.x;
	result.y = y + v.y;
	return result;
}

Vec2 Vec2::operator - (const Vec2& v) const {
	Vec2 result;
	result.x = x - v.x;
	result.y = y - v.y;
	return result;
}

Vec2 Vec2::operator * (const float n) const {
	Vec2 result;
	result.x = x * n;
	result.y = y * n;
	return result;
}

Vec2 Vec2::operator / (const float n) const {
	Vec2 result;
	result.x = x / n;
	result.y = y / n;
	return result;
}

Vec2& Vec2::operator += (const Vec2& v) {
	x += v.x;
	y += v.y;
	return *this;
}

Vec2& Vec2::operator -= (const Vec2& v) {
	x -= v.x;
	y -= v.y;
	return *this;
}

Vec2& Vec2::operator *= (const float n) {
	x *= n;
	y *= n;
	return *this;
}

Vec2& Vec2::operator /= (const float n) {
	x /= n;
	y /= n;
	return *this;
}

Vec2 Vec2::operator - () {
	Vec2 result;
	result.x = x * -1;
	result.y = y * -1;
	return result;
}

void Vec2::Add(const Vec2& v) {
	x += v.x;
	y += v.y;
}

void Vec2::Sub(const Vec2& v) {
	x -= v.x;
	y -= v.y;
}

void Vec2::Scale(const float n) {
	x *= n;
	y *= n;
}

void Vec2::Rotate(const float degree)
{
	float l = Magnitude();

	float rad = -(degree * 3.141592f) / 180.0f;

	x = x * cos(rad) - y * sin(rad);
	y = x * sin(rad) + y * cos(rad);

	Normalize();

	x *= l;
	y *= l;
}

void Vec2::RotateAroundPoint(const Vec2& point, const float degree)
{
	float rad = -(degree * 3.141592f) / 180.0f;

	float tempX = x - point.x;
	float tempY = y - point.y;

	float rotatedX = tempX * cos(rad) - tempY * sin(rad);
	float rotatedY = tempX * sin(rad) + tempY * cos(rad);

	x = rotatedX + point.x;
	y = rotatedY + point.y;
}

float Vec2::Magnitude() const {
	return sqrtf(x * x + y * y);
}

float Vec2::MagnitudeSquared() const {
	return (x * x + y * y);
}

Vec2& Vec2::Normalize() {
	float length = Magnitude();
	if (length != 0.0) {
		x /= length;
		y /= length;
	}
    return *this;
}

Vec2 Vec2::UnitVector() const {
	Vec2 result = Vec2(0, 0);
	float length = Magnitude();
	if (length != 0.0) {
		result.x = x / length;
		result.y = y / length;
	}
    return result;
}

Vec2 Vec2::Normal() const {
	return Vec2(y, -x).Normalize();
}

Vec2 Vec2::ProjectOnto(const Vec2& vec2)
{
	Vec2 unitVec2 = vec2.Normal();

	float dot = Dot(unitVec2);

	return unitVec2 * dot;
}

Vec2 Vec2::Reflect(const Vec2& normal)
{
	Vec2 current = *this;

	return current - normal * (current.Dot(normal) * 2);
}

float Vec2::Dot(const Vec2& v) const {
    return (x * v.x) + (y * v.y);
}

float Vec2::Cross(const Vec2& v) const {
	return (x * v.y) - (y * v.x);
}