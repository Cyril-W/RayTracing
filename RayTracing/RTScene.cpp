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
	Vector3 forward = _dir.normalize();
	Vector3 right(Vector3(0, 1, 0).crossProduct(forward));
	Vector3 up(right.crossProduct(forward));

	_worldToCamera = Mat4x4(
		Vector4(right, 0),
		Vector4(up, 0),
		Vector4(forward, 0),
		Vector4(_center, 1)
	);
}

Camera::Camera(float x, float y, float z, float a, float b, float c, float f) : _center(x, y, z), _dir(a, b, c), _focal(f) {

}

void Camera::render(const char* imgName, int width, int height, const std::list<Object*>& objects) {
	BMP bmp(width, height);

	//Matrix44f cameraToWorld; // to determine !!!
	auto scale = tan(_focal  * acos(-1) / 360);
	auto aspectRatio = width / (float)height;
	//Vector3 orig; // usefull? Camera origin?
	// cameraToWorld.multVecMatrix(Vec3f(0), orig);

	for (auto j = 0; j < height; ++j) {
		for (auto i = 0; i < width; ++i) {
			float x = (2 * (i + 0.5) / (float)width - 1) * aspectRatio * scale;
			float y = (1 - 2 * (j + 0.5) / (float)height) * scale;

			Vector3 dir;
			//cameraToWorld.multDirMatrix(Vec3f(x, y, -1), dir);
			// dir.normalize(); // TO DO !!!

			Ray r(_center, dir);
			Vector4 color = getPixelColor(r, objects/*, lights,*/);
			bmp.set_pixel(x, y, color[0], color[1], color[2], color[3]);
		}
	}

	char* fileName;
	strcat(fileName, "file/");
	strcat(fileName, imgName);
	std::cout << "Writing image at: " << fileName << std::endl;
	bmp.write(fileName);
}

Vector4 Camera::getPixelColor(const Ray& r, const std::list<Object*>& objects/*, const std::list<Light*> &lights*/) {
	bool anyHit = false, isHit = false;
	Vector3 currInter, closestInter = Vector3(INFINITY, INFINITY, INFINITY);
	for (auto const& o : objects) {
		isHit = o->intersect(r, currInter);
		anyHit = anyHit || isHit;
		if (isHit) {
			if (currInter.distance(r.orig) < closestInter.distance(r.orig)) {
				closestInter = currInter;
			}
			std::cout << "Ray intersecte cet object ? Oui At " << currInter << std::endl;
		} else {
			std::cout << "Ray intersecte cet object ? Non" << std::endl;
		}
	}
	return anyHit ? Vector4(255, 255, 255, 255) : Vector4();
}
