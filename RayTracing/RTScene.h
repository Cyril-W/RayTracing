#include <list>

#include "RTMath.h"
#include "RTGeometry.h"

#pragma once

struct Light {
	Vector3 center;
	// TODO: float intensity;

	Light();
	Light(Vector3 c);
	Light(float x, float y, float z);

	friend std::ostream& operator << (std::ostream& os, const Light& l);
};

class Camera {
private:
	Vector3 _center;
	Vector3 _dir;
	float _focal;
	Mat4x4 _cameraToWorld;
public:
	Camera(Vector3 c = Vector3(), Vector3 d = Vector3(1, 1, -1), float f = 90);
	Camera(float x = 0, float y = 0, float z = 0, float a = 1, float b = 1, float c = -1, float f = 90);
	Mat4x4 computeCameraToWorld();
	void render(const char* imgName, int width, int height, const std::list<Object*>& objects, const std::list<Light*> &lights) const;
	bool castRay(const Ray& r, Vector3& intersection, Vector3& normalAtIntern, const std::list<Object*>& objects) const;
	Vector4 calculateLight(const Vector3& intersection, const Vector3& normalAtInter, const std::list<Light*>& lights) const;

	friend std::ostream& operator << (std::ostream& os, const Camera& c);
};
