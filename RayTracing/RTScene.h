#include <list>

#include "RTMath.h"
#include "RTGeometry.h"

#pragma once

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
	void render(const char* imgName, int width, int height, const std::list<Object*>& objects);
	bool castRay(const Ray& r, Vector3& intersection, const std::list<Object*>& objects/*, const std::list<Light*> &lights*/);

	friend std::ostream& operator << (std::ostream& os, const Camera& c);
};
