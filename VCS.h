#ifndef VCS_H
#define VCS_H

#include "Object.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


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
	int limit = 10;
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

	vector<float> bg_color;
	vector<vector<vector<int> > > render_this;
	
	VCS();
	void generate_Rays();
	void set_bg_color();
	void render();
	
	vector<float> recursive_ray_trace(Ray&,int,float);
	pair<Object *, pair<float, vector<float> > > intersect(Ray &r);
	tuple<float, Ray, Ray> get_acc_illumination(Ray &, pair<Object *, pair<float, vector<float> > > &);
};

#endif