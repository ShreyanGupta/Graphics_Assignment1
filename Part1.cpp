#include "Head.h"

using namespace std;

int main(int argc, char const *argv[])
{
	ifstream fin("inputs/" + (string)(argv[1]));
	string s;
	
	fin >> s; // Camera:
	Camera cam;
	fin >> cam.posn.PVec[0];
	fin >> cam.posn.PVec[1];
	fin >> cam.posn.PVec[2];
	float w;
	fin >> w;
	cam.dirn.DirVec[0] = w-cam.posn.PVec[0];
	fin >> w;
	cam.dirn.DirVec[1] = w-cam.posn.PVec[1];
	fin >> w;
	cam.dirn.DirVec[2] = w-cam.posn.PVec[2];
	cout << "dz = " << cam.dirn.DirVec[2] << endl;
	
	fin >> s; // Light-sources:
	int no_light;
	fin >> no_light;
	vector<Point> LightSrc (no_light);
	for (int i = 0; i < no_light; i++)
	{
		fin >> LightSrc[i].x;
		fin >> LightSrc[i].y;
		fin >> LightSrc[i].z;
	}

	fin >> s; // Spheres:
	int no_sph;
	fin >> no_sph;
	vector<Sphere> Spheres (no_sph);
	for (int i = 0; i < no_sph; i++)
	{
		fin >> Spheres[i].center.x;
		fin >> Spheres[i].center.y;
		fin >> Spheres[i].center.z;
		fin >> Spheres[i].radius;
	}

	fin >> s; // Triangles:
	int no_pol;
	fin >> no_pol;
	vector<Polygon> Polygons;
	for (int i = 0; i < no_pol; i++)
	{
		int no_pts;
		fin >> no_pts;
		Polygon p = Polygon(no_pts);
		for (int j = 0; j < no_pts; j++)
		{
			fin >> Triangles[i].pts[j].x;
			fin >> Triangles[i].pts[j].y;
			fin >> Triangles[i].pts[j].z;
		}
		Polygons.push_back(p);
	}
	cout << "Parsing done! \n";
	return 0;
}