#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <utility>

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
};


class Triangle : public Object {
	vector<float> a;
	vector<float> b;
	vector<float> c;
	vector<float> nml;

	
	Triangle() : Object();

	void Calc_Normal();

};
// class Polygon : public Object {
// 	vector< pair<float, float> > pts;
// 	Ray plane;
// };

#endif