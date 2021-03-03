#include <iostream>

#pragma once

struct Vector3 {
	float x, y, z;

	Vector3(float a = 0, float b = 0, float c = 0);
	bool operator== (const Vector3& other);

	float dotProduct(const Vector3& other) const;
	Vector3 crossProduct(const Vector3& other) const;
	float distance(const Vector3& other) const;
	Vector3 normalize() const;
	Vector3 clamp(const float &lo, const float &hi);

	friend std::ostream& operator << (std::ostream& os, const Vector3& p);
	friend Vector3 operator+ (const Vector3& a, const Vector3& b);
	friend Vector3 operator- (const Vector3& a, const Vector3& b);
	friend Vector3 operator* (const Vector3& a, float b);
	friend Vector3 operator* (const Vector3& a, int b);
};

struct Vector4 {
	float values[4];

	Vector4(float a = 0, float b = 0, float c = 0, float d = 0);
	Vector4(Vector3 v, float d = 0);
	const float& operator[] (int index) const;
	float& operator[] (int index);

	friend std::ostream& operator << (std::ostream& os, const Vector4& v);
};

struct Mat4x4 {
	Vector4 columns[4];

	Mat4x4();
	Mat4x4(Vector4 v1, Vector4 v2, Vector4 v3, Vector4 v4);
	const Vector4& operator[] (int index) const;
	Vector4& operator[] (int index);

	friend std::ostream& operator << (std::ostream& os, const Mat4x4& m);
	friend Vector4 operator*(const Mat4x4& m, const Vector4& v);
};