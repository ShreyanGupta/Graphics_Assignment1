#ifndef RAY_H
#define RAY_H

#include <vector>
#include <utility>
#include <cmath>
#include <tuple>
#include <iostream>

using namespace std;

class Ray{
private:
	vector<float> d;	// length 4 vector specifying direction
	vector<float> p;	// length 4 vector specifying offset point
	float a;
	float b;
	float c;
public:
	// Ray operator*(const Matrix &m);
	Ray();
	Ray(vector<float> d, vector<float> p);

	vector<float> get_d() { return d;}
	vector<float> get_p() { return p;}
	tuple<float, float, float> get_abc();
	vector<float> get_point(float t);

	void set_d(vector<float> d);
	void set_p(vector<float> p);

	void add_offset(vector<float> &o);
	void add_dirn(vector<float> &dn);

	void print();
};

#endif