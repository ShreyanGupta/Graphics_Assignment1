#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Matrix
{
	vector<vector<float> > t;
	Matrix();
	Matrix Inverse();
	Matrix operator*(const Matrix&);
	Matrix& operator*=(const Matrix&);
	void print();
};