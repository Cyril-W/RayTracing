#include <iostream>

#include "RTGeometry.h"

/*
	Material
*/
std::ostream& operator << (std::ostream& os, const Material& m) {
	os << "Material/ " << m.name << " of color " << m.color << std::endl;
	return os;
}

Material::Material(const char* n) : name(n), color(0, 0, 0, 255) {}

Material::Material(const char* n, Vector4 c) : name(n), color(c) {}

Material::Material(const char* n, float r, float g, float b, float a) : name(n), color(r, g, b, a) {}

/*
	Ray
*/
std::ostream& operator << (std::ostream& os, const Ray& r) {
	os << "Ray/ At " << r.orig << " Looking " << r.dir << std::endl;
	return os;
}

Ray::Ray() : orig(), dir() {}

Ray::Ray(Vector3 o, Vector3 d) : orig(o), dir(d) {}

Ray::Ray(float a, float b, float c, float x, float y, float z) : orig(a, b, c), dir(x, y, z) {}

/*
	Plane
*/
std::ostream& operator << (std::ostream& os, const Plane& p) {
	os << "Plane/ At " << p._point << " Looking " << p._normal << std::endl;
	return os;
}

Plane::Plane(Vector3 p, Vector3 n) {
	if (n == Vector3(0, 0, 0)) {
		std::cerr << "Invalid Plane Definition: n = (0 ; 0 ; 0)" << std::endl;
		return;
	} else {
		_point = p;
		_normal = n.normalize();
	}
}

Plane::Plane(float x, float y, float z, float a, float b, float c) {
	if (a == 0 && b == 0 && c == 0) {
		std::cerr << "Invalid Plane Definition: a = b = c = 0" << std::endl;
		return;
	} else {
		_point = Vector3(x, y, z);
		_normal = Vector3(a, b, c).normalize();
	}
}

bool Plane::intersect(const Ray& r, Vector3& inter) const {
	auto denom = _normal.dotProduct(r.dir);
	if (denom > 1e-6 || denom < -1e-6) {
		auto num = _point - r.orig;
		auto t = num.dotProduct(_normal) / denom;
		if (t >= 0) {
			inter = r.orig + r.dir * t;
			return true;
		}
	}
	return false;
}

/*
	Sphere
*/
std::ostream& operator << (std::ostream& os, const Sphere& s) {
	os << "Sphere/ At " << s._center << " Radius " << s._r << std::endl;
	return os;
}

Sphere::Sphere(Vector3 c, float r) : _center(c), _r(r) {}

Sphere::Sphere(float x, float y, float z, float r) : _center(Vector3(x, y, z)), _r(r) {}

bool Sphere::intersect(const Ray& r, Vector3& inter) const {
	auto OC = _center - r.orig;
	auto OA = OC.dotProduct(r.dir);
	if (OA >= 0) {
		auto AC2 = OC.dotProduct(OC) - pow(OA, 2);
		auto r2 = pow(_r, 2);
		if (AC2 < r2) {
			auto PA = sqrt(r2 - AC2);
			auto inter1 = r.orig + r.dir * (OA - PA);
			auto inter2 = r.orig + r.dir * (OA + PA);
			inter = r.orig.distance(inter1) > r.orig.distance(inter2) ? inter1 : inter2;
			return true;
		} if (AC2 == r2) {
			inter = r.orig + r.dir * OA;
			return true;
		}
	}
	return false;
}
