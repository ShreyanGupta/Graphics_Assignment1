#ifndef OBJECT_H
#define OBJECT_H

#include "Matrix.h"
#include "Ray.h"

#include <vector>
#include <utility>
#include <memory>

// #include <opencv2/opencv.hpp>

using namespace std;

#define eps 0.00001
#define c_limit 0.01
// #define s_pow 4

Ray make_ray(float a, float b, float c, float d, float e, float f);
float dot(Ray &p, Ray &q);
void add_vecs(vector<float> &a1, vector<float> &a2);
void mult_const(vector<float> &a, float f);

class Object{
public:	
	vector<float> k_ads;
	float kr, kt, eta;
	float s_pow;
	vector<float> color;
	Matrix t;
	Object();
	void set_color(int r, int g, int b);
	Ray reflected(Ray &r, Ray &n);
	Ray refracted(Ray &r, Ray &n);
	virtual Ray normal(Ray &r, pair<float, vector<float> > &pr) = 0;
	virtual pair<float, vector<float> > intersection(Ray &r) = 0;
};

class Sphere : public Object {
public:
	float radius;
	pair<float, vector<float> > intersection(Ray &r);
	Ray normal(Ray &r, pair<float, vector<float> > &pr);
};


class Triangle : public Object {
public:
	vector<float> a;
	vector<float> b;
	vector<float> c;
	vector<float> nml;

	Triangle();

	void Calc_Normal();

	pair<float, vector<float> > intersection(Ray &r);
	Ray normal(Ray &r, pair<float, vector<float> > &pr);
};



#endif