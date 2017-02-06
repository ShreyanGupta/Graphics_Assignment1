#ifndef OBJECT_H
#define OBJECT_H

#include "Matrix.h"
#include "Ray.h"

#include <vector>
#include <utility>

using namespace std;

class Object{
	Matrix t;
	vector<float> k_ads;
	vector<int> color;
public:	
	Object();
	void set_color(int r, int g, int b);
	virtual Ray normal(Ray r, pair<float, vector<float> > &pr) = 0;
	// virtual Ray reflected_ray(Ray r) = 0;
	virtual pair<float, vector<float> > intersection(Ray r) = 0;
};

class Sphere : public Object {
	float radius;
	pair<float, vector<float> > intersection(Ray r);
	Ray normal(Ray r, pair<float, vector<float> > &pr);
};


class Triangle : public Object {
	pair<float, vector<float> > intersection(Ray r);
	Ray normal(Ray r, pair<float, vector<float> > &pr);
};
// class Polygon : public Object {
// 	vector< pair<float, float> > pts;
// 	Ray plane;
// };

#endif