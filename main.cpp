#include "Object.h"
#include "VCS.h"
#include <fstream>
using namespace std;

VCS parse_vcs(istream &fin);


int main(int argc, char const *argv[])
{
	// ifstream fin("inputs/" + (string)(argv[1]));
	ifstream fin("inputs/input1.txt");
	string s;
	// CHECKING OVERLOADING:
		// Matrix m1;
		// m1.t[0][0] = 5;
		// m1.t[0][1] = -2;
		// m1.t[0][2] = 2;
		// m1.t[0][3] = 7;
		// m1.t[1][0] = 1;
		// m1.t[1][1] = 0;
		// m1.t[1][2] = 0;
		// m1.t[1][3] = 3;
		// m1.t[2][0] = -3;
		// m1.t[2][1] = 1;
		// m1.t[2][2] = 5;
		// m1.t[2][3] = 0;
		// m1.t[3][0] = 3;
		// m1.t[3][1] = -1;
		// m1.t[3][2] = -9;
		// m1.t[3][3] = 4;

		// Matrix m2;
		// for (int i = 0; i < 4; i++)
		// 	for (int j = 0; j < 4; j++)
		// 		m2.t[i][j] = (i+j)%2;
		// m1.print();
		// cout << "-> m1, m2 -> \n";
		// m2.print();
		// Matrix m3 = m1*m2;
		// cout << "using * : \n";
		// m3.print();
		// m1.print();
		// m1 *= m2;
		// cout << "using *= : \n";
		// m1.print();
		// cout << "Inverse is : \n";
		// m1.Calc_Inverse();
		// m1.print_Inv();

	// TEST RAY - SPHERE :

	VCS vcs = parse_vcs(fin);
	cout << "Parsing done! \n";
	
	Ray r = make_ray(0,0,1, 0,0,0);
	r.print();
	cout << vcs.obj_vec.size() << endl;
	for(auto ptr : vcs.obj_vec){
		auto intersection = ptr->intersection(r);
		cout << intersection.first << " " << endl;
	}
	
	return 0;
}