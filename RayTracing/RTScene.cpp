//#include <string>

#include "RTScene.h"
#include "libs/BMP.h"

/*
	Camera
*/
std::ostream& operator << (std::ostream& os, const Camera& c) {
	os << "Camera/ At " << c._center << " Looking " << c._dir << " Focal " << c._focal << std::endl;
	return os;
}

Camera::Camera(Vector3 c, Vector3 d, float f) : _center(c), _dir(d), _focal(f) {
	_cameraToWorld = computeCameraToWorld();
}

Camera::Camera(float x, float y, float z, float a, float b, float c, float f) : _center(x, y, z), _dir(a, b, c), _focal(f) {
	_cameraToWorld = computeCameraToWorld();
}

Mat4x4 Camera::computeCameraToWorld() {
	Vector3 up(0, 1, 0);

	Vector3 forward = _dir.normalize();
	Vector3 right(up.crossProduct(forward).normalize());
	up = Vector3(forward.crossProduct(right).normalize());

	return Mat4x4(
		Vector4(right, 0),
		Vector4(up, 0),
		Vector4(forward, 0),
		Vector4(_center, 1)
	);
}

void Camera::render(const char* imgName, int width, int height, const std::list<Object*>& objects) {
	BMP bmp(width, height);

	auto scale = tan(_focal  * acos(-1) / 360);
	auto aspectRatio = width / (float)height;

	for (auto j = 0; j < height; ++j) {
		for (auto i = 0; i < width; ++i) {
			float x = (2 * (i + 0.5) / (float)width - 1) * aspectRatio * scale;
			float y = (1 - 2 * (j + 0.5) / (float)height) * scale;

			auto dir = _cameraToWorld * Vector4(x, y, -1, 1);
			auto direction = Vector3(dir[0], dir[1], dir[2]).normalize() ;

			Ray r(_center, direction);
			Vector3 intersection = Vector3(INFINITY, INFINITY, INFINITY);
			bool anyHit = castRay(r, intersection, objects/*, lights,*/);
			/*if (i + j % 25 == 0 && anyHit) {
				std::cout << (i + j) << " - x=" << x << " y=" << y << " intersect=" << intersection << std::endl;
			}*/
			Vector4 color = anyHit ? Vector4(255, 255, 255, 255) : Vector4();
			bmp.set_pixel(i, j, color[0], color[1], color[2], color[3]);
		}
	}
	
	std::cout << "Writing image at: " << imgName << std::endl;
	bmp.write(imgName);
}

bool Camera::castRay(const Ray& r, Vector3& intersection, const std::list<Object*>& objects/*, const std::list<Light*> &lights*/) {
	bool anyHit = false, isHit = false;
	Vector3 currInter;
	for (auto const& o : objects) {
		isHit = o->intersect(r, currInter);
		anyHit = anyHit || isHit;
		if (isHit) {
			if (currInter.distance(r.orig) < intersection.distance(r.orig)) {
				intersection = currInter;
			}
			//std::cout << "Ray intersecte cet object ? Oui At " << currInter << std::endl;
		} else {
			//std::cout << "Ray intersecte cet object ? Non" << std::endl;
		}
	}
	return anyHit;
}
