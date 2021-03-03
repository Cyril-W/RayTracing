#include <iostream>

#include "RTMath.h"

/*
	Vector3
*/
std::ostream& operator << (std::ostream& os, const Vector3& p) {
	os << "(" << p.x << " ; " << p.y << " ; " << p.z << ")";
	return os;
}

Vector3::Vector3(float a, float b, float c) : x(a), y(b), z(c) {}

bool Vector3::operator== (const Vector3& other) {
	return x == other.x && y == other.y && z == other.z;
}

Vector3 operator+ (const Vector3& a, const Vector3& b) {
	return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vector3 operator- (const Vector3& a, const Vector3& b) {
	return a + (b * -1);
}

Vector3 operator* (const Vector3& a, const float b) {
	return Vector3(a.x * b, a.y * b, a.z * b);
}

Vector3 operator* (const Vector3& a, const int b) {
	return a * (float)b;
}

float Vector3::dotProduct(const Vector3& other) const {
	return x * other.x + y * other.y + z * other.z;
}

Vector3 Vector3::crossProduct(const Vector3& other) const {
	return Vector3(
		y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x
	);
}

float Vector3::distance(const Vector3& other) const {
	return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2) + pow(z - other.z, 2));
}

Vector3 Vector3::normalize() const {
	auto magnitude = this->distance(Vector3(0, 0, 0));
	return Vector3(x / magnitude, y / magnitude, z / magnitude);
}

/*
	Vector4
*/
std::ostream& operator << (std::ostream& os, const Vector4& v) {
	os << "(" << v[0] << " ; " << v[1] << " ; " << v[2] << " ; " << v[3] << ")";
	return os;
}

Vector4::Vector4(float a, float b, float c, float d) : values{ a, b, c, d } {}

Vector4::Vector4(Vector3 v, float d) : values{ v.x, v.y, v.z, d } {}

const float& Vector4::operator[] (int index) const {
	return values[index];
}

float& Vector4::operator[] (int index) {
	return values[index];
}

/*
	Mat4x4
*/
std::ostream& operator << (std::ostream& os, const Mat4x4& m) {
	os << m[0] << std::endl;
	os << m[1] << std::endl;
	os << m[2] << std::endl;
	os << m[3] << std::endl;
	return os;
}

Mat4x4::Mat4x4() {
	columns[0] = Vector4(1, 0, 0, 0);
	columns[1] = Vector4(0, 1, 0, 0);
	columns[2] = Vector4(0, 0, 1, 0);
	columns[3] = Vector4(0, 0, 0, 1);
}

Mat4x4::Mat4x4(Vector4 v1, Vector4 v2, Vector4 v3, Vector4 v4) : columns{ v1, v2, v3, v4 } {}

const Vector4& Mat4x4::operator[] (int index) const {
	return columns[index];
}

Vector4& Mat4x4::operator[] (int index) {
	return columns[index];
}

Vector4 operator*(const Mat4x4& m, const Vector4& v) {
	return Vector4(
		m[0][0] * v[0] + m[1][0] * v[1] + m[2][0] * v[2] + m[3][0] * v[3],
		m[0][1] * v[0] + m[1][1] * v[1] + m[2][1] * v[2] + m[3][1] * v[3],
		m[0][2] * v[0] + m[1][2] * v[1] + m[2][2] * v[2] + m[3][2] * v[3],
		m[0][3] * v[0] + m[1][3] * v[1] + m[2][3] * v[2] + m[3][3] * v[3]
	);
}