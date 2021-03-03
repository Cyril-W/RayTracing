#include <list>

#include "RTMath.h"
#include "RTGeometry.h"

#pragma once

class Camera {
private:
	Vector3 _center;
	Vector3 _dir;
	float _focal;
	Mat4x4 _worldToCamera;
public:
	Camera(Vector3 c = Vector3(), Vector3 d = Vector3(), float f = 90);
	Camera(float x = 0, float y = 0, float z = 0, float a = 0, float b = 0, float c = 0, float f = 90);

	void render(const char* imgName, int width, int height, const std::list<Object*>& objects);
	Vector4 getPixelColor(const Ray& r, const std::list<Object*>& objects/*, const std::list<Light*> &lights*/);

	friend std::ostream& operator << (std::ostream& os, const Camera& c);
};
