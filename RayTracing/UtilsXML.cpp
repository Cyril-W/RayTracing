#include "UtilsXML.h"
#include "libs/rapidxml_utils.hpp"

using namespace rapidxml;

bool UtilsXML::createMaterials(const char* docName, std::list<Material*>& materials) {
	std::cout << "Reading file at: " << docName << " -> Creating Materials" << std::endl;
	file<> xmlFile(docName);
	xml_document<> doc;
	doc.parse<0>(xmlFile.data());
	auto root = doc.first_node("root")->first_node("materials");
	if (root) {
		for (auto mat = root->first_node(); mat; mat = mat->next_sibling()) {
			auto c = mat->first_node("c");
			if (c) {
				Material newMat(
					mat->name(),
					std::stof(c->first_attribute("b")->value()),
					std::stof(c->first_attribute("g")->value()),
					std::stof(c->first_attribute("r")->value()),
					std::stof(c->first_attribute("a")->value())
				);
				std::cout << newMat;
				materials.push_back((Material*)(&newMat));
			} else {
				std::cerr << "Unable to construct the material " << mat->name() << " (c missing)" << std::endl;
			}
		}
		return true;
	}
	std::cerr << "Unable to find node <materials>" << std::endl;
	return false;
}

bool UtilsXML::createObjects(const char* docName, std::list<Object*>& objects) {
	std::cout << "Reading file at: " << docName << " -> Creating Objects" << std::endl;
	file<> xmlFile(docName);
	xml_document<> doc;
	doc.parse<0>(xmlFile.data());
	auto root = doc.first_node("root")->first_node("objects");
	if (root) {
		for (auto plane = root->first_node("plane"); plane; plane = plane->next_sibling("plane")) {
			auto p = plane->first_node("p");
			auto n = plane->first_node("n");
			if (p && n) {							
				Plane newPlane(
					std::stof(p->first_attribute("x")->value()),
					std::stof(p->first_attribute("y")->value()),
					std::stof(p->first_attribute("z")->value()),
					std::stof(n->first_attribute("a")->value()),
					std::stof(n->first_attribute("b")->value()),
					std::stof(n->first_attribute("c")->value())
				);
				std::cout << newPlane;
				objects.push_back((Object*)(&newPlane));
			} else {
				std::cerr << "Unable to construct the plane " << plane->name() << " (p or n missing)" << std::endl;
			}
		}
		for (auto sphere = root->first_node("sphere"); sphere; sphere = sphere->next_sibling("sphere")) {
			auto c = sphere->first_node("c");
			auto r = sphere->first_node("r");
			if (c && r) {
				Sphere newSphere(
					std::stof(c->first_attribute("x")->value()),
					std::stof(c->first_attribute("y")->value()),
					std::stof(c->first_attribute("z")->value()),
					std::stof(r->value())
				);
				std::cout << newSphere;
				objects.push_back((Object*)(&newSphere));
			} else {
				std::cerr << "Unable to construct the sphere " << sphere->name() << " (c or r missing)" << std::endl;
			}
		}
		return true;
	}
	std::cerr << "Unable to find node <objects>" << std::endl;
	return false;
}

bool UtilsXML::createLights(const char* docName, std::list<Light*>& lights) {
	std::cout << "Reading file at: " << docName << " -> Creating Lights" << std::endl;
	file<> xmlFile(docName);
	xml_document<> doc;
	doc.parse<0>(xmlFile.data());
	auto root = doc.first_node("root")->first_node("lights");
	if (root) {
		for (auto light = root->first_node("c"); light; light = light->next_sibling("c")) {		
			Light newLight(
				std::stof(light->first_attribute("x")->value()),
				std::stof(light->first_attribute("y")->value()),
				std::stof(light->first_attribute("z")->value())
			);
			std::cout << newLight;
			lights.push_back((Light*)(&newLight));
		}
		return true;
	}
	std::cerr << "Unable to find node <lights>" << std::endl;
	return false;
}

bool UtilsXML::createCamera(const char* docName, Camera& cam) {
	std::cout << "Reading file at: " << docName << " -> Creating Camera" << std::endl;
	file<> xmlFile(docName);
	xml_document<> doc;
	doc.parse<0>(xmlFile.data());
	auto root = doc.first_node("root")->first_node("camera");
	if (root) {
		auto c = root->first_node("c");
		auto d = root->first_node("d");
		auto f = root->first_node("f");
		if (c && d && f) {
			cam = Camera(
				std::stof(c->first_attribute("x")->value()),
				std::stof(c->first_attribute("y")->value()),
				std::stof(c->first_attribute("z")->value()),
				std::stof(d->first_attribute("a")->value()),
				std::stof(d->first_attribute("b")->value()),
				std::stof(d->first_attribute("c")->value()),
				std::stof(f->value())
			);
			std::cout << cam;
			return true;
		} else {
			std::cerr << "Unable to construct the camera (c, d or f missing)" << std::endl;
			return false;
		}
	}
	std::cerr << "Unable to find node <camera>" << std::endl;
	return false;
}
