#include <list>

#include "RTScene.h"
#include "libs/rapidxml.hpp"

#pragma once

struct UtilsXML {
	static bool createMaterials(const char* docName, std::list<Material*>& materials);
	static bool createObjects(const char* docName, std::list<Object*>& objects);
	static bool createLights(const char* docName, std::list<Light*>& lights);
	static bool createCamera(const char* docName, Camera& cam);
};
