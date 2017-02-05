#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <utility>

class Object{
	Matrix t;
	vector<float> k_ads
	vector<int> color;
public:	
	Object();
	void set_color(int r, int g, int b);
	virtual Ray normal(Ray r) = 0;
	virtual Ray reflected_ray(Ray r) = 0;
	virtual float intersection(Ray r) = 0;
};

class Sphere : public Object {
	float radius;
	
};

class Polygon : public Object {
	vector< pair<float, float> > pts;
	Ray plane;
};

#endif