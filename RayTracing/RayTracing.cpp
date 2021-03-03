#include <iostream>

#include "RTGeometry.h"
#include "RTScene.h"
#include "UtilsXML.h"

/*
void bindObjectToMaterials(std::list<Object*>& objects, std::list<Material*>& materials) {
	auto mat = plane->first_node("mat");
	if (mat) {
		for (auto const& m : materials) {
			if (m->name == mat->value()) {
				newPlane.mat = &mat;
			}
		}
		//std::cerr << "Unable to create material (mat missing)" << std::endl;					
	} else {
		std::cerr << "Unable to create material for " << plane->name() << " (mat missing)" << std::endl;
	}
}
*/

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

	// TODO: Bind objects to materials
	
	std::cout << std::endl;	

	camera.render("files/img_test.bmp", 600, 500, objects, lights);
}
