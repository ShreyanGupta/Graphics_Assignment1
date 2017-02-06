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
	float del_x = (window[1] - window[0])/pixel_x;
	float del_y = (window[2] - window[3])/pixel_y;
	for (int i = 0; i < 4; i++)
		M.t[0][i] = u[i];
	for (int i = 0; i < 4; i++)
		M.t[1][i] = v[i];
	for (int i = 0; i < 4; i++)
		M.t[2][i] = n[i];
	// M is ready!
	vector<float> p_e (4);
	p_e[0] = window[0] - eye_vcs[0];
	p_e[1] = window[2] - eye_vcs[1];
	p_e[2] = - eye_vcs[2];
	p_e[3] = 1;
	Ray r_ij(M.Vec_Mul(p_e),M.Vec_Mul(eye_vcs));
	r_ij.add_offset(origin_vcs);

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
		r_ij.add_dirn(add_x);
		for (int j = 0; j < pixel_y; j++)
		{
			// add (0,-j*dy,0,1) * M to d
			r_ij.add_dirn(add_y);
			// RAY IN WCS:
			// call rrt.
		}
		r_ij.add_dirn(sub_y);
	}
}

vector<float> VCS::recursive_ray_trace(Ray &r, int n)
{

}