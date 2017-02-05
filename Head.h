#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Matrix
{
	vector<vector<float> > trans;
	Matrix();
};

inline Matrix()
{
	trans = vector<vector<float> > (4, vector<float> (4));
}

struct Point
{
	vector<float> p;
	Point();
};

inline Point::Point()
{
	p = vector<float>(4);
	p[3] = 1;
}

struct Direction
{
	vector<float> dir_vec;
	Direction();
};

inline Direction()
{
	dir_vec = vector<float> (3);
}

struct Sphere
{
	Point center;
	Matrix m;
	float radius;
};

struct Triangle
{
	vector<Point> pts;
	Triangle();
};

inline Triangle::Triangle()
{
	pts = vector<Point> (3);
}