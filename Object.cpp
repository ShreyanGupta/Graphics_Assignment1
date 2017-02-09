#include "Object.h"

#include <cmath>

Ray make_ray(float a, float b, float c, float d, float e, float f){
	vector<float> x(4,1), y(4,1);
	x[0] = a;
	x[1] = b;
	x[2] = c;
	y[0] = d;
	y[1] = e;
	y[2] = f;
	return Ray(x,y);
}

float dot(Ray &p, Ray &q){
	auto p_d = p.get_d();
	auto q_d = q.get_d();
	float ans = 0;
	for(int i=0; i<3; ++i){
		ans += p_d[i] * q_d[i];
	}
	return ans/sqrt(get<0>(p.get_abc()) * get<0>(q.get_abc()));
}

void add_vecs(vector<float> &a1, vector<float> &a2)
{
	for (int i = 0; i < 3; i++)
		a1[i] += a2[i];
}

void mult_const(vector<float> &a, float f)
{
	for (int i = 0; i < 3; i++)
		a[i] *= f;
}

Object::Object(){
	k_ads = vector<float>(3);
	color = vector<float>(3);
}

void Object::set_color(int r, int g, int b){
	color[2] = std::max(0, std::min(255, r));
	color[1] = std::max(0, std::min(255, g));
	color[0] = std::max(0, std::min(255, b));
}

Ray Object::reflected(Ray &r, Ray &n){
	auto r_d = r.get_d();
	auto n_d = n.get_d();
	float factor = -2 * dot(r,n) * sqrt(get<0>(r.get_abc()) / get<0>(n.get_abc()));
	for(int i=0; i<3; ++i){
		n_d[i] = n_d[i] * factor + r_d[i];
	}
	return Ray(n_d, n.get_p());
}

Ray Object::refracted(Ray &l, Ray &n){
	auto l_d = l.get_d();
	auto n_d = n.get_d();
	float cos_i = dot(l,n);
	float cos_t = sqrt(eta*eta - 1 + cos_i*cos_i)/eta;
	for(int i=0; i<3; ++i){
		l_d[i] = eta * (l_d[i] + cos_i*n_d[i]) - cos_t * n_d[i];
	}
	return Ray(l_d, n.get_p());
}

Ray Sphere::normal(Ray &r, pair<float, vector<float> > &pr){
	return Ray(t.transform_inv_transpose(pr.second), r.get_point(pr.first));
}

pair<float, vector<float> > Sphere::intersection(Ray &r){
	Ray t_r = t.transform_inv(r);
	auto abc = t_r.get_abc();
	get<2>(abc) -= radius*radius;
	float disc = get<1>(abc) * get<1>(abc) - get<0>(abc) * get<2>(abc);
	if(disc < 0) return make_pair(-2, vector<float>(4,1));
	else{
		float tt = (-get<1>(abc) - sqrt(disc))/get<0>(abc);
		// if(tt < eps*100) tt = (-get<1>(abc) + sqrt(disc))/get<0>(abc);
		return make_pair(tt, t_r.get_point(tt));
	}
}


Triangle::Triangle()
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

	a[0] = axcx;
	a[1] = aycy;
	a[2] = azcz;

	b[0] -= c[0];
	b[1] -= c[1];
	b[2] -= c[2];
}

Ray Triangle::normal(Ray &r, pair<float, vector<float> > &pr){
	vector<float> p = r.get_point(pr.first);
	auto d = r.get_d();
	// cout << "Normal TRI : ";
	if(d[0]*nml[0] + d[1]*nml[1] + d[2]*nml[2] < 0)
	{
		// cout << nml[0] << " " << nml[1] << " " << nml[2] << endl;
		return Ray(nml, p);
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			nml[i] *= -1;
			// cout << nml[i] << " ";
		}
		// cout << endl;
		return Ray(nml,p);
	}
}

pair<float, vector<float> > Triangle::intersection(Ray &r){
	// p - 
	// x.print();
	// x.print_Inv();
	vector<float> s = r.get_d();
	vector<float> p = r.get_p();

	float b2s1_b1s2 = b[2]*s[1] - b[1]*s[2];
	float b0s2_b2s0 = b[0]*s[2] - b[2]*s[0];
	float b1s0_b0s1 = b[1]*s[0] - b[0]*s[1];

	float denom =  a[0]*b2s1_b1s2 + a[1]*b0s2_b2s0 + a[2]*b1s0_b0s1;

	float u = (float(1.0)/denom)*( (p[0] - c[0])*b2s1_b1s2 + (p[1] - c[1])*b0s2_b2s0 + (p[2] - c[2])*b1s0_b0s1);

	float v = (float(1.0)/denom)*( (p[0] - c[0])*(a[1]*s[2] - a[2]*s[1]) + (p[1] - c[1])*(a[2]*s[0] - a[0]*s[2]) + (p[2] - c[2])*(a[0]*s[1] - a[1]*s[0]) );
	
	float t = (float(1.0)/denom)*( (p[0] - c[0])*(a[1]*b[2] - a[2]*b[1]) + (p[1] - c[1])*(a[2]*b[0] - a[0]*b[2]) + (p[2] - c[2])*(a[0]*b[1] - a[1]*b[0]) );
	// for (int i = 0; i < 4; i++)
	// 	cout << uvwt[i] << " ";
	if (u >= eps && (v >= eps) && ((1 - u - v) >= eps))
	{
		// PoI inside triangle!
		return make_pair(t,vector<float> (0));
	}
	else
	{
		return make_pair(-1,vector<float> (0));
	}
}
