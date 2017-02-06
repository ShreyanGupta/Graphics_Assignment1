#include "VCS.h"

int main(int argc, char const *argv[])
{
	Ray r1 = make_ray(1,0,0,0,0,0);
	r1.print();

	Triangle t;
	t.a[0] = 5;
	t.a[1] = -3;
	t.a[2] = 2;

	t.b[0] = 5;
	t.b[1] = -4;
	t.b[2] = -1;

	t.c[0] = 11;
	t.c[1] = 7;
	t.c[2] = 1;

	t.Calc_Normal();
	auto tray = t.intersection(r1);
	Ray nml = t.normal(r1,tray);
	cout << "t is : " << tray.first << endl;
	cout << "Normal is : \n";
	nml.print();

	return 0;
}