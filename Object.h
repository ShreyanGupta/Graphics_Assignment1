#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <utility>

class Object{
	Matrix transformation;
	vector<float> k_ads
public:	
	virtual Ray normal(Ray r) = 0;
	virtual Ray reflected_ray(Ray r) = 0;
};

class Sphere : public Object {
	float radius;
	
};

class Polygon : public Object {
	vector< pair<float, float> > pts;
	Ray plane;
};

#endif