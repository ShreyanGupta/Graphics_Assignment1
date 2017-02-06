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
	r.print();
	t.print();
	t.print_Inv();
	Ray t_r = t.transform_inv(r);
	cout << "print t_r\n"; t_r.print(); cout << endl;
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
	vector<float> p = r.get_point(pr.first);
	Ray ans (nml,p);
	return ans;
}

// Ray Ploygon::reflected_ray(Ray r){
	
// }

pair<float, vector<float> > Triangle::intersection(Ray r){
	// p - 
	Matrix x;
	for (int i = 0; i < 4; i++)
		x.t[0][i] = a[i];
	for (int i = 0; i < 4; i++)
		x.t[1][i] = b[i];
	for (int i = 0; i < 4; i++)
		x.t[2][i] = c[i];
	vector<float> rd = r.get_d();
	for (int i = 0; i < 3; i++)
		x.t[3][i] = -rd[i];
	x.t[3][3] = 0;
	x.Calc_Inverse();
	x.print();
	x.print_Inv();
	vector<float> uvwt = r.get_p();
	uvwt = x.Inv_Vec_Mul(uvwt);
	for (int i = 0; i < 4; i++)
		cout << uvwt[i] << " ";
	if (uvwt[0] >= eps && (uvwt[1] >= eps) && (uvwt[2] >= eps))
	{
		// PoI inside triangle!
		return make_pair(uvwt[3],vector<float> (0));
	}
	else
	{
		return make_pair(-1,vector<float> (0));
	}
}
