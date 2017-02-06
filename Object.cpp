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
	get<2>(abc) -= radius*radius;
	float disc = get<1>(abc) * get<1>(abc) - get<0>(abc) * get<2>(abc);
	if(disc < 0) return make_pair(-2, vector<float>());
	else{
		float tt = (-get<1>(abc) - sqrt(disc))/get<0>(abc);
		return make_pair(tt, t_r.get_point(tt));
	}
}

Triangle::Triangle() : Object()
{
	a = vector<float> (4,1);
	b = vector<float> (4,1);
	c = vector<float> (4,1);
	nml = vector<float> (4,1);
}

void Triangle::Calc_Normal()
{
	// cross prod (a-b)*(a-c)
	float axbx = a[0] - b[0];
	float ayby = a[1] - b[1];
	float azbz = a[2] - b[2];

	float axcx = a[0] - c[0];
	float aycy = a[1] - c[1];
	float azcz = a[2] - c[2];

	nml[0] = ayby*azcz - azbz*aycy;
	nml[1] = azbz*axcx - axbx*azcz;
	nml[2] = axbx*aycy - ayby*axcx;
}

Ray Triangle::normal(Ray r, pair<float, vector<float> > &pr){
	return r;
}

// Ray Ploygon::reflected_ray(Ray r){
	
// }

pair<float, vector<float> > Triangle::intersection(Ray r){

}
