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
	vector<float> eye_vcs; // in vcs 1*4
	vector<float> origin_vcs; // in WCS 1*4
	vector<float> window; // 4 ki length wl wr wt wb
	Matrix M;
	int pixel_x;
	int pixel_y;

	vector<vector<vector<int> > > render_this;
	VCS();
	void generate_Rays();

};

#endif