// #include "Object.h"
#include "VCS.h"

#include <fstream>
#include <cmath>

void parse_sphere(int n, vector<Object*> obj_vector, istream &fin);
void parse_triangles(int n, vector<Object*> obj_vector, istream &fin);
vector<LightSrc> parse_light_source(int n, istream &fin);


VCS parse_vcs(istream &fin){
	string temp;
	VCS vcs;
	
	fin >> temp >> vcs.u[0] >> vcs.u[1] >> vcs.u[2];
	fin >> temp >> vcs.v[0] >> vcs.v[1] >> vcs.v[2];
	fin >> temp >> vcs.n[0] >> vcs.n[1] >> vcs.n[2];
	fin >> temp >> vcs.eye_vcs[0] >> vcs.eye_vcs[1] >> vcs.eye_vcs[2];
	fin >> temp >> vcs.origin_vcs[0] >> vcs.origin_vcs[1] >> vcs.origin_vcs[2];
	fin >> temp >> vcs.window[0] >> vcs.window[1] >> vcs.window[2] >> vcs.window[3];
	fin >> temp >> vcs.pixel_x >> vcs.pixel_y;
	fin >> temp >> vcs.Ia;
	fin >> temp >> vcs.bg_color[0] >> vcs.bg_color[1] >> vcs.bg_color[2];
	vcs.set_bg_color();

	while((fin >> temp, temp).compare("end") != 0){
		if(temp.compare("light-sources:") == 0){
			int n;
			fin >> n;
			vcs.lights = parse_light_source(n,fin);
		}
		else if(temp.compare("spheres:") == 0){
			int n;
			fin >> n;
			parse_sphere(n, vcs.obj_vec, fin);
		}
		else if(temp.compare("triangles:") == 0){
			int n;
			fin >> n;
			parse_triangles(n, vcs.obj_vec, fin);
		}
	}

	return vcs;
}

vector<LightSrc> parse_light_source(int n, istream &fin){
	string temp;
	vector<LightSrc> v;
	for(int i=0; i<n; ++i){
		vector<float> src(4,1);
		float intensity;
		fin >> temp;
		fin >> src[0] >> src[1] >> src[2];
		fin >> temp;
		fin >> intensity;
		v.emplace_back(src, intensity);
	}
	return v;
}

void parse_sphere(int n, vector<Object*> obj_vector, istream &fin){
	string temp;
	for(int i=0; i<n; ++i){
		Sphere *sphere = new Sphere();
		while((fin >> temp, temp).compare("end") != 0){
			if(temp.compare("c:") == 0){
				float x, y, z;
				fin >> x >> y >> z;
				sphere->t *= Matrix(1,0,0,0, 0,1,0,0, 0,0,1,0, x,y,z,1);
			}
			else if(temp.compare("r:") == 0){
				float r;
				sphere->radius = r;
			}
			else if(temp.compare("rotate:") == 0){
				float angle;
				fin >> temp >> angle;
				float s = sin(angle * M_PI/180);
				float c = cos(angle * M_PI/180);
				if(temp.compare("x") == 0) sphere->t *= Matrix(1,0,0,0, 0,c,s,0, 0,-s,c,0, 0,0,0,1);
				if(temp.compare("y") == 0) sphere->t *= Matrix(c,0,-s,0, 0,1,0,0, s,0,c,0, 0,0,0,1);
				if(temp.compare("z") == 0) sphere->t *= Matrix(c,s,0,0, -s,c,0,0, 0,0,1,0, 0,0,0,1);
			}
			else if(temp.compare("shear:") == 0){
				float c1, c2, c3, c4, c5, c6;
				fin >> c1 >> c2 >> c3 >> c4 >> c5 >> c6;
				sphere->t *= Matrix(1,c1,c2,0, c3,1,c4,0, c5,c6,1,0, 0,0,0,1);
			}
			else if(temp.compare("scale:") == 0){
				float x, y, z;
				fin >> x >> y >> z;
				sphere->t *= Matrix(x,0,0,0, 0,y,0,0, 0,0,z,0, 0,0,0,1);
			}
			else if(temp.compare("color:") == 0){
				float r, g, b;
				fin >> r >> g >> b;
				sphere->set_color(r,g,b);
			}
			else if(temp.compare("K:") == 0){
				float ka, kd, ks;
				fin >> ka >> kd >> ks;
				sphere->k_ads[0] = ka;
				sphere->k_ads[1] = kd;
				sphere->k_ads[2] = ks;
			}
		}
		sphere->t.Calc_Inverse();
		obj_vector.push_back(sphere);
	}
}

void parse_triangles(int n, vector<Object*> obj_vector, istream &fin){
	string temp;
	for (int i = 0; i < n; i++)
	{
		Triangle* t = new Triangle();
		fin >> t->a[0] >> t->a[1] >> t->a[2];
		fin >> t->b[0] >> t->b[1] >> t->b[2];
		fin >> t->c[0] >> t->c[1] >> t->c[2];
		fin >> temp >> t->k_ads[0] >> t->k_ads[1] >> t->k_ads[2];
		t->Calc_Normal();
		obj_vector.push_back(t);
	}
}

