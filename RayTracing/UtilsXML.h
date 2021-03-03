#include <list>

#include "RTScene.h"

#pragma once

struct UtilsXML {
	static bool createObjects(const char* docName, std::list<Object*>& objects);
	//static std::list<std::unique_ptr<Light>> createObjects(const char* docName);
	static bool createCamera(const char* docName, Camera& cam);
};
