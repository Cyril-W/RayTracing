#include "RTScene.h"
#include "libs/BMP.h"

/*
	Light
*/
std::ostream& operator << (std::ostream& os, const Light& l) {
	os << "Light/ At " << l.center << std::endl;
	return os;
}

Light::Light() : center() {}

Light::Light(Vector3 c) : center(c) {}

Light::Light(float x, float y, float z) : center(Vector3(x, y, z)) {}

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

void Camera::render(const char* imgName, int width, int height, const std::list<Object*>& objects, const std::list<Light*> &lights) const {
	BMP bmp(width, height);

	auto scale = tan(_focal  * acos(-1) / 360);
	// TODO: handle the case where heigh > width
	auto aspectRatio = width / (float)height;

	for (auto j = 0; j < height; ++j) {
		for (auto i = 0; i < width; ++i) {
			float x = (2 * (i + 0.5) / (float)width - 1) * aspectRatio * scale;
			float y = (2 * (j + 0.5) / (float)height - 1) * scale;

			auto dir = _cameraToWorld * Vector4(x, y, -1, 1);
			auto direction = Vector3(dir[0], dir[1], dir[2]).normalize() ;

			Ray r(_center, direction);
			Vector3 intersection = Vector3(INFINITY, INFINITY, INFINITY), normalAtInter;
			bool anyHit = castRay(r, intersection, normalAtInter, objects);

			auto color = Vector4();
			if (anyHit) {
				// TODO: calculate closest light
				auto light = *lights.begin();
				auto lightDir = (light->center - intersection).normalize();
				auto tempColor = calculateLight(lightDir, normalAtInter, lights);
				// TODO: cast secondary rays to cast shadow
				/*auto tempRay = Ray(intersection, lightDir);
				intersection = Vector3(INFINITY, INFINITY, INFINITY);
				anyHit = castRay(tempRay, intersection, normalAtInter, objects);*/
				color = /*anyHit ? Vector4(0, 0, 0, 255):*/  tempColor;
			}
			bmp.set_pixel(i, j, color[0], color[1], color[2], color[3]);
		}
	}
	
	std::cout << "Writing image at: " << imgName << std::endl;
	bmp.write(imgName);
}

bool Camera::castRay(const Ray& r, Vector3& intersection, Vector3& normalAtInter, const std::list<Object*>& objects) const {
	bool anyHit = false, isHit = false;
	Vector3 currInter;
	for (auto const& o : objects) {
		isHit = o->intersect(r, currInter);
		anyHit = anyHit || isHit;
		if (isHit && currInter.distance(r.orig) < intersection.distance(r.orig)) {
			intersection = currInter;
			normalAtInter = o->getNormal(intersection);
		}
	}
	return anyHit;
}

Vector4 Camera::calculateLight(const Vector3& lightDir, const Vector3& normalAtInter, const std::list<Light*>& lights) const {
	auto li = lightDir.dotProduct(normalAtInter);	
	auto matColor = Vector4(0, 0, 255, 255);
	auto lightFactor = Vector3(255, 255, 255) * li;
	return Vector4(
		((Vector3(matColor[0], matColor[1], matColor[2]) + lightFactor) * 0.5f).clamp(0, 255),
		matColor[3]
	);
}
