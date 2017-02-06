#include "Object.h"

#include <cmath>

Object::Object(){
	k_ads = vector<float>(3);
	color = vector<int>(3);
}

void Object::set_color(int r, int g, int b){
	color[0] = std::max(0, std::min(255, r));
	color[1] = std::max(0, std::min(255, g));
	color[2] = std::max(0, std::min(255, b));
}

Ray Sphere::normal(Ray r, pair<float, vector<float> > &pr){
	return Ray(t.transform_inv_transpose(pr.second), r.get_point(pr.first));
}

// Ray Sphere::reflected_ray(Ray r){
	
// }

pair<float, vector<float> > Sphere::intersection(Ray r){
	Ray t_r = t.transform_inv(r);
	auto abc = t_r.get_abc();
	abc.get<2> -= radius*radius;
	float disc = abc.get<1>() * abc.get<1>() - abc.get<0>() * abc.get<2>();
	if(disc < 0) return make_pair(-2, vector<float>());
	else{
		float tt = (-abc.get<1>() - sqrt(disc))/abc.get<0>();
		return make_pair(tt, t_r.get_point(tt));
	}
}

Ray Triangle::normal(Ray r, pair<float, vector<float> > &pr){
	return r;
}

// Ray Ploygon::reflected_ray(Ray r){
	
// }

pair<float, vector<float> > Triangle::intersection(Ray r){

}
