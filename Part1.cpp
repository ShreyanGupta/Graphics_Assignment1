#include "Head.h"

using namespace std;

int main(int argc, char const *argv[])
{
	ifstream fin("inputs/" + (string)str(argv[1]));
	string s;
	fin >> s; //camera
	Camera cam;
	fin >> cam.posn.x;
	fin >> cam.posn.y;
	fin >> cam.posn.z;
	float w;
	fin >> w;
	cam.dirn.dx = w-cam.posn.x;
	fin >> w;
	cam.dirn.dy = w-cam.posn.y;
	fin >> w;
	cam.dirn.dz = w-cam.posn.z;
	cout << "dz = " << cam.dirn.dz << endl;
	return 0;
}