#include <iostream>
#include <fstream>

using namespace std;

struct Point
{
	float x;
	float y;
	float z;
};

struct Direction
{
	float dx;
	float dy;
	float dz;
};

struct Camera
{
	Point posn;
	Direction dirn;
};
