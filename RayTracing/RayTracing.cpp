#include <iostream>

#include "RTScene.h"
#include "UtilsXML.h"

int main() {
	auto sceneFile = "scene.xml";

	Camera camera = Camera(0);
	if (!UtilsXML::createCamera(sceneFile, camera)) {
		return 0;
	}

	std::list<Object*> objects;
	UtilsXML::createObjects(sceneFile, objects);

	//std::list<Light*> lights;
	//UtilsXML::createLights(sceneFile, lights);

	std::cout << std::endl;	

	camera.render("img_test.bmp", 800, 600, objects);
}
