#include <iostream>

#include "RTScene.h"
#include "UtilsXML.h"

int main() {
	auto sceneFile = "files/scene.xml";

	Camera camera = Camera(0);
	if (!UtilsXML::createCamera(sceneFile, camera)) {
		return 0;
	}

	std::cout << std::endl;

	std::list<Object*> objects;
	UtilsXML::createObjects(sceneFile, objects);

	//std::cout << std::endl;

	//std::list<Light*> lights;
	//UtilsXML::createLights(sceneFile, lights);

	std::cout << std::endl;	

	camera.render("files/img_test.bmp", 500, 500, objects);
}
