#include <iostream>

#include "RTMath.h"

#pragma once

struct Material {
	const char* name;
	Vector4 color;
	// TODO: Reflexion
	// TODO: Transparency

	Material(const char* n);
	Material(const char* n, Vector4 c);
	Material(const char* n, float r, float g, float b, float a);

	friend std::ostream& operator << (std::ostream& os, const Material& r);
};

struct Ray {
	const Vector3 orig;
	const Vector3 dir;

	Ray();
	Ray(Vector3 o, Vector3 d);
	Ray(float a = 0, float b = 0, float c = 0, float x = 0, float y = 0, float z = 0);

	friend std::ostream& operator << (std::ostream& os, const Ray& r);
};

class Object {
public:
	// TODO: Material* mat;

	virtual bool intersect(const Ray& r, Vector3& inter) const = 0;
	virtual Vector3 getNormal(const Vector3& inter) const = 0;
};

class Plane : Object {
private:
	Vector3 _point;
	Vector3 _normal;

public:
	Plane(Vector3 p, Vector3 n);
	Plane(float a = 0, float b = 0, float c = 0, float x = 0, float y = 0, float z = 0);

	bool intersect(const Ray& r, Vector3& inter) const override;
	Vector3 getNormal(const Vector3& inter) const override;

	friend std::ostream& operator << (std::ostream& os, const Plane& p);
};

class Sphere : Object {
private:
	Vector3 _center;
	float _r;

public:
	Sphere(Vector3 c = Vector3(0, 0, 0), float r = 0);
	Sphere(float x = 0, float y = 0, float z = 0, float r = 0);

	bool intersect(const Ray& r, Vector3& inter) const override;
	Vector3 getNormal(const Vector3& inter) const override;

	friend std::ostream& operator << (std::ostream& os, const Sphere& s);
};