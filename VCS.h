#ifndef VCS_H
#define VCS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class VCS
{
	vector<float> u;
	vector<float> v;
	vector<float> n;
	vector<float> eye_vcs; // in vcs
	vector<float> origin_vcs; // 
	vector<float> window;
	VCS(){
		u = vector<float>(4,1);
		v = vector<float>(4,1);
		n = vector<float>(4,1);
		eye_vcs = vector<float>(4,1);
		origin_vcs = vector<float>(4,1);
		window = vector<float>(4,0);
	}
};

#endif