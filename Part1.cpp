#include "Matrix.h"

using namespace std;

int main(int argc, char const *argv[])
{
	ifstream fin("inputs/" + (string)(argv[1]));
	string s;
	// CHECKING OVERLOADING:
		Matrix m1;
		m1.t[0][0] = 5;
		m1.t[0][1] = -2;
		m1.t[0][2] = 2;
		m1.t[0][3] = 7;
		m1.t[1][0] = 1;
		m1.t[1][1] = 0;
		m1.t[1][2] = 0;
		m1.t[1][3] = 3;
		m1.t[2][0] = -3;
		m1.t[2][1] = 1;
		m1.t[2][2] = 5;
		m1.t[2][3] = 0;
		m1.t[3][0] = 3;
		m1.t[3][1] = -1;
		m1.t[3][2] = -9;
		m1.t[3][3] = 4;

		Matrix m2;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				m2.t[i][j] = (i+j)%2;
		m1.print();
		cout << "-> m1, m2 -> \n";
		m2.print();
		Matrix m3 = m1*m2;
		cout << "using * : \n";
		// m3.print();
		m1.print();
		// m1 *= m2;
		// cout << "using *= : \n";
		// m1.print();
		cout << "Inverse is : \n";
		m1.Calc_Inverse();
		m1.print_Inv();


	
	cout << "Parsing done! \n";
	return 0;
}