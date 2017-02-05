#include "Object.h"

#include <fstream>
#include <cmath>

void parse_sphere(int n, vector<Object> obj_vector, istream &fin){
	string temp;
	for(int i=0; i<n; ++i){
		Sphere sphere;
		while((fin >> temp).compare("end") != 0){
			if(temp.compare("c:") == 0){
				float x, y, z;
				fin >> x >> y >> z;
				sphere.t *= Matrix(1,0,0,0, 0,1,0,0, 0,0,1,0, x,y,z,1);
			}
			if(temp.compare("r:") == 0){
				float r
				sphere.radius = r;
			}
			if(temp.compare("rotate:") == 0){
				float angle;
				fin >> temp >> angle;
				float s = sin(angle * PI/180);
				float c = cos(angle * PI/180);
				if(temp.compare("x") == 0) sphere.t *= Matrix(1,0,0,0, 0,c,s,0, 0,-s,c,0, 0,0,0,1);
				if(temp.compare("y") == 0) sphere.t *= Matrix(c,0,-s,0, 0,1,0,0, s,0,c,0, 0,0,0,1);
				if(temp.compare("z") == 0) sphere.t *= Matrix(c,s,0,0, -s,c,0,0, 0,0,1,0, 0,0,0,1);
			}
			if(temp.compare("shear:") == 0){
				float c1, c2, c3, c4, c5, c6;
				fin >> c1 >> c2 >> c3 >> c4 >> c5 >> c6;
				sphere.t *= Matrix(1,c1,c2,0, c3,1,c4,0, c5,c6,1,0, 0,0,0,1);
			}
			if(temp.compare("scale:") == 0){
				float x, y, z;
				fin >> x >> y >> z;
				sphere.t *= Matrix(x,0,0,0, 0,y,0,0, 0,0,z,0, 0,0,0,1);
			}
			if(temp.compare("color:") == 0){
				float r, g, b;
				fin >> r >> g >> b;
				sphere.set_color(r,g,b);
			}
			if(temp.compare("K:") == 0){
				float ka, kd, ks;
				fin >> ka >> kd >> ks;
				sphere.k_ads[0] = ka;
				sphere.k_ads[1] = kd;
				sphere.k_ads[2] = ks;
			}
		}
		sphere.t.Calc_Inverse();
		obj_vector.push_back(sphere);
	}
}