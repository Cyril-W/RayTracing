#include <iostream>

#include "RTGeometry.h"
#include "RTScene.h"
#include "UtilsXML.h"

int main() {
	auto sceneFile = "files/scene.xml";

	Camera camera(0);
	if (!UtilsXML::createCamera(sceneFile, camera)) {
		return 0;
	}

	std::cout << std::endl;

	std::list<Light*> lights;
	UtilsXML::createLights(sceneFile, lights);

	std::cout << std::endl;
	std::list<Material*> materials;
	UtilsXML::createMaterials(sceneFile, materials);

	std::cout << std::endl;

	std::list<Object*> objects;
	UtilsXML::createObjects(sceneFile, objects);
	
	std::cout << std::endl;	

	camera.render("files/img_test.bmp", 600, 500, objects, lights);
}
