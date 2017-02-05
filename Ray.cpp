#include "Ray.h"

#include <cmath>

Ray::Ray(){
	d = vector<float>(4,0);
	p = vector<float>(4,0);
	d[3] = p[3] = 1;
}

Ray::Ray(vector<float> d, vector<float> p){
	this->d = d;
	this->p = p;
	for(int i=0; i<3; ++i){
		a += d[i] * d[i];
		b += p[i] * d[i];
		c += p[i] * p[i];
	}
}

// Ray Ray::multiply(Matrix &m, bool inverse){
// 	Ray r (	
// 		inverse ? m.Inv_Vec_Mul(this->d) : m.Vec_Mul(this->d),
// 		inverse ? m.Inv_Vec_Mul(this->p) : m.Vec_Mul(this->p)
// 	);
// 	return r;
// }

void Ray::set_d(vector<float> d){
	a = b = 0;
	for(int i=0; i<3; ++i){
		this->d[i] = d[i];
		a += d[i] * d[i];
		b += p[i] * d[i];
		// c += p[i] * p[i];
	}
}

void Ray::set_p(vector<float> p){
	b = c = 0;
	for(int i=0; i<3; ++i){
		this->p[i] = p[i];
		// a += d[i] * d[i];
		b += p[i] * d[i];
		c += p[i] * p[i];
	}
}

tuple<float, float, float> Ray::get_abc(){
	return make_tuple(a,b,c);
}

vector<float> Ray::get_point(float t){
	vector<float> ret(4,1);
	for(int i=0; i<3; ++i){
		ret[i] = p[i] + t*d[i];
	}
	return ret;
}