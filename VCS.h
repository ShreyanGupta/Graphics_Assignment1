#ifndef VCS_H
#define VCS_H

#include "Object.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

inline Ray make_ray(float a, float b, float c, float d, float e, float f){
	vector<float> x(4,1), y(4,1);
	x[0] = a;
	x[1] = b;
	x[2] = c;
	y[0] = d;
	y[1] = e;
	y[2] = f;
	return Ray(x,y);
}

struct LightSrc
{
	vector<float> src;
	float intensity;
	LightSrc(vector<float> src, float intensity){
		this->src = src;
		this->intensity = intensity;
	}
};


class VCS
{
public:
	vector<float> u;
	vector<float> v;
	vector<float> n;
	vector<float> eye_vcs; // in vcs 1*4
	vector<float> origin_vcs; // in WCS 1*4
	vector<float> window; // 4 ki length wl wr wt wb
	Matrix M;
	int pixel_x;
	int pixel_y;

	float Ia;
	vector<Object*> obj_vec;
	vector<LightSrc> lights;

	vector<int> bg_color;
	vector<vector<vector<int> > > render_this;
	
	VCS();
	void generate_Rays();
	void set_bg_color();
	vector<float> recursive_ray_trace(Ray&,int);
};

#endif