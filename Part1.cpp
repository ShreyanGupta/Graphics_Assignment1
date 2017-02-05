#include "Matrix.h"

using namespace std;

int main(int argc, char const *argv[])
{
	ifstream fin("inputs/" + (string)(argv[1]));
	string s;
	// CHECKING OVERLOADING:
		Matrix m1;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				m1.t[i][j] = (i+j)%3;
		Matrix m2;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				m2.t[i][j] = (i+j)%2;
		m1.print();
		cout << "-> m1, m2 -> \n";
		m2.print();
		Matrix m3 = m1*m2;
		cout << "using * : \n";
		m3.print();
		m1 *= m2;
		cout << "using *= : \n";
		m1.print();

	
	cout << "Parsing done! \n";
	return 0;
}