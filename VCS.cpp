#include "VCS.h"

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

VCS::VCS(){
	u = vector<float>(4,1);
	v = vector<float>(4,1);
	n = vector<float>(4,1);
	eye_vcs = vector<float>(4,1);
	origin_vcs = vector<float>(4,1);
	window = vector<float>(4,0);
	bg_color = vector<int> (3,0);
}

void VCS::set_bg_color()
{
	bg_color[0] = std::max(0, std::min(255, bg_color[0]));
	bg_color[1] = std::max(0, std::min(255, bg_color[1]));
	bg_color[2] = std::max(0, std::min(255, bg_color[2]));
}

void VCS::generate_Rays()
{
	render_this = vector<vector<vector<int> > > (pixel_x, vector<vector<int> > (pixel_y, vector<int> (3)));

	float del_x = (window[1] - window[0])/pixel_x;
	float del_y = (window[2] - window[3])/pixel_y;
	for (int i = 0; i < 3; i++)
		M.t[0][i] = v[i];
	for (int i = 0; i < 3; i++)
		M.t[1][i] = u[i];
	for (int i = 0; i < 3; i++)
		M.t[2][i] = n[i];
	// M is ready!
	vector<float> p_e (4);
	p_e[0] = window[0] - eye_vcs[0];
	p_e[1] = window[2] - eye_vcs[1];
	p_e[2] = - eye_vcs[2];
	p_e[3] = 1;
	Ray r_ij(M.Vec_Mul(p_e),M.Vec_Mul(eye_vcs));
	r_ij.add_offset(origin_vcs);

	r_ij.print();

	vector<float> add_x (4,0);
	add_x[0] = del_x;
	add_x[3] = 1;
	add_x = M.Vec_Mul(add_x);

	vector<float> add_y (4,0);
	add_y[1] = -del_y;
	add_y[3] = 1;
	add_y = M.Vec_Mul(add_y);

	vector<float> sub_y (4,0);
	sub_y[1] = del_y*(pixel_y);
	sub_y[3] = 1;

	for (int i = 0; i < pixel_x; i++)
	{
		cout << i << endl;
		r_ij.add_dirn(add_x);
		for (int j = 0; j < pixel_y; j++)
		{
			// add (0,-j*dy,0,1) * M to d
			r_ij.add_dirn(add_y);
			// cout << "i, j = " << i << " " << j << endl;
			// r_ij.print(); cout << endl;
			auto rgb = recursive_ray_trace(r_ij,0);
			for (int k = 0; k < 3; k++)
			render_this[i][j][k] = min(rgb.first[k]*rgb.second,(float)255.0);
			// RAY IN WCS:
			// call rrt.
		}
		r_ij.add_dirn(sub_y);
	}
}

pair<Object *, pair<float, vector<float> > > VCS::intersect(Ray &r){
	pair<float, vector<float> > t_min = make_pair(1000000000, vector<float>());
	Object *first_obj = NULL;
	for(auto ptr : obj_vec){
		auto intersect = ptr->intersection(r);
		if(intersect.first < eps) continue;
		if(intersect.first < t_min.first){
			first_obj = ptr;
			t_min = intersect;
		}
	}
	return make_pair(first_obj, t_min);
}

pair<float,Ray> VCS::get_acc_illumination(Ray &r, pair<Object *, pair<float, vector<float> > > &input){
	// auto final_color = //ambient
	auto ans = input.first->k_ads[0] * Ia;
	auto normal = input.first->normal(r, input.second);
	auto reflected = input.first->reflected(r, normal);
	for (auto light : lights)
	{
		// Ray : p ->
		auto np = normal.get_p();
		auto d = light.src;
		for (int i = 0; i < 3; i++)
			d[i] -= np[i];
		Ray p_src(d, np);
		auto l_in = intersect(p_src);
		if (l_in.first != NULL)
			continue;
		// add Id, Is.
		ans += input.first->k_ads[1] * light.intensity * -dot(r, normal);
		ans += input.first->k_ads[2] * light.intensity * pow(dot(p_src, reflected), s_pow);
	}
	return make_pair(ans,reflected);
}

pair<vector<int>, float> VCS::recursive_ray_trace(Ray &r, int n){
	if(n > limit) return make_pair(bg_color,1);
	auto q = intersect(r);
	if(q.first == NULL) return make_pair(bg_color,1);
	// if (n == 0) cout << "Not background. \n";
	auto int_ray = get_acc_illumination(r, q);
	float intensity = int_ray.first;
	auto coh_Reflect = recursive_ray_trace(int_ray.second, n+1);
	intensity += coh_Reflect.second;
	return make_pair(q.first->color,intensity);
}

void VCS::render()
{
	ofstream fout("matrix.txt");
	fout << pixel_x << " " << pixel_y << "\n";
	for (int i = 0; i < pixel_x; i++)
	{
		for (int j = 0; j < pixel_y; j++)
			fout << render_this[i][j][0] << " " << render_this[i][j][1] << " " << render_this[i][j][2] << " ";
		fout << "\n";
	}
}




