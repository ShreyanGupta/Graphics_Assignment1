#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "VCS.h"

struct LightSrc
{
	vector<float> src;
	float intensity;
};

class Scene
{
	VCS vcs;
	float Ia;
	vector<Object> obj_vec;
	vector<LightSrc> lights;
};

#endif