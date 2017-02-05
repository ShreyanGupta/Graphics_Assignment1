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

Ray Sphere::normal(Ray r, float t){
	
}

Ray Sphere::reflected_ray(Ray r){

}

float Sphere::intersection(Ray r){
	// Ray t_r = r.multiply(this->t,true);
	auto abc = t_r.get_abc();
	abc.get<2> -= radius*radius;
	float disc = abc.get<1>() * abc.get<1>() - abc.get<0>() * abc.get<2>();
	if(disc < 0) return -1;
	else return (-abc.get<1>() - sqrt(disc))/abc.get<0>();
}

Ray Polygon::normal(Ray r){

}

Ray Ploygon::reflected_ray(Ray r){
	
}

Ray Polygon::intersection(Ray r){

}
