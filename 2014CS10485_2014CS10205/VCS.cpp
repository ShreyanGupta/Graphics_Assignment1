#include "VCS.h"


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


	// vector<float> add_x_avg (4,0);
	// add_x_avg[0] = del_x/3.0;
	// add_x_avg[3] = 1;
	// add_x_avg = M.Vec_Mul(add_x_avg);

	// vector<float> add_y_avg (4,0);
	// add_y_avg[1] = -del_y/3.0;
	// add_y_avg[3] = 1;
	// add_y_avg = M.Vec_Mul(add_y_avg);

	// vector<float> sub_y_avg (4,0);
	// sub_y_avg[1] = del_y;
	// sub_y_avg[3] = 1;

	for (int i = 0; i < pixel_x; i++)
	{
		cout << i << endl;
		r_ij.add_dirn(add_x);
		for (int j = 0; j < pixel_y; j++)
		{
			// add (0,-j*dy,0,1) * M to d
			r_ij.add_dirn(add_y);
		// 			vector<float> rd = r_ij.get_d();
		// 			for (int x = 0; x < 3; x++)
		// 				rd[x] -= (add_x_avg[x] + add_y_avg[x]);

		// // r1 : R(-1,-1)
		// 			Ray r1 (rd, r_ij.get_p());
		// 			vector<float> avg (3,0);

		// 			for (int k = -1; k < 2; k++)
		// 			{
		// 				for (int l = -1; l < 2; l++)
		// 				{
		// 					auto rgb = recursive_ray_trace(r1,0);
		// 					for (int x = 0; x < 3; x++)
		// 						avg[x] += rgb.first[x]*rgb.second;
		// 					r1.add_dirn(add_y_avg);
		// 				}
		// 				r1.add_dirn(sub_y_avg);
		// 				r1.add_dirn(add_x_avg);
		// 			}

		// 	for (int k = 0; k < 3; k++)
		// 		render_this[i][j][k] = min(float(avg[k]/9.0),(float)255.0);

			// divide all by 9.
			// cout << "i, j = " << i << " " << j << endl;
			// r_ij.print(); cout << endl;
			// RAY IN WCS:
			// call rrt.
			auto rgb = recursive_ray_trace(r_ij,0);

			for (int k = 0; k < 3; k++)
				render_this[i][j][k] = min(rgb.first[k]*rgb.second,(float)255.0);
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
	// normal.print();
	auto reflected = input.first->reflected(r, normal);
	for (auto light : lights)
	{
		// Ray : p -> src
		auto np = normal.get_p();
		auto d = light.src;
		for (int i = 0; i < 3; i++)
			d[i] -= np[i];
		Ray p_src(d, np);
		auto l_in = intersect(p_src);
		if (l_in.first != NULL)
			continue;
		// add Id, Is.
		float kd_dot = dot(p_src,normal);
		if (kd_dot >= 0.0)
		{
			ans += input.first->k_ads[1] * light.intensity * kd_dot;
			ans += input.first->k_ads[2] * light.intensity * pow(max(dot(p_src, reflected), (float)0), input.first->s_pow);			
		}
	}
	// cout << "     " << ans << endl;
	return make_pair(ans,reflected);
}

pair<vector<int>, float> VCS::recursive_ray_trace(Ray &r, int n){
	if(n == limit) return make_pair(bg_color,0);
	auto q = intersect(r);
	if(q.first == NULL) return make_pair(bg_color,1);
	auto int_ray = get_acc_illumination(r, q);
	float intensity = int_ray.first;
	
	// if (n == 0) cout << "     " << intensity << endl;

	auto coh_Reflect = recursive_ray_trace(int_ray.second, n+1);
	intensity += coh_Reflect.second;
	return make_pair(q.first->color,intensity);
}

// void VCS::render()
// {
// 	ofstream fout("matrix.txt");
// 	fout << pixel_x << " " << pixel_y << "\n";
// 	for (int i = 0; i < pixel_x; i++)
// 	{
// 		for (int j = 0; j < pixel_y; j++)
// 			fout << render_this[i][j][0] << " " << render_this[i][j][1] << " " << render_this[i][j][2] << " ";
// 		fout << "\n";
// 	}
// }

void VCS::render()
{
	float a1 = 0.75;
	float a2 = 0.25;
	ofstream fout("matrix.txt");
	fout << (pixel_x-2) << " " << (pixel_y-2) << "\n";
	for (int i = 1; i < pixel_x-1; i++)
	{
		for (int j = 1; j < pixel_y-1; j++){
			int avg[3];
			avg[0] = (a1)*render_this[i][j][0] + (a2 * 0.25)*(render_this[i+1][j+1][0] + render_this[i+1][j-1][0] + render_this[i-1][j+1][0] + render_this[i-1][j-1][0]);
			avg[1] = (a1)*render_this[i][j][1] + (a2 * 0.25)*(render_this[i+1][j+1][1] + render_this[i+1][j-1][1] + render_this[i-1][j+1][1] + render_this[i-1][j-1][1]);
			avg[2] = (a1)*render_this[i][j][2] + (a2 * 0.25)*(render_this[i+1][j+1][2] + render_this[i+1][j-1][2] + render_this[i-1][j+1][2] + render_this[i-1][j-1][2]);
			fout << avg[0] << " " << avg[1] << " " << avg[2] << " ";
		}
		fout << "\n";
	}
}




