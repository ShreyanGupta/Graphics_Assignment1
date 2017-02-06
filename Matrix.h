#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Ray;

struct Matrix
{
	vector<vector<float> > t;
	vector<vector<float> > t_1;
	Matrix();
	Matrix(float,float,float,float,float,float,float,float,float,float,float,float,float,float,float,float);

	Matrix operator*(const Matrix&);
	Matrix& operator*=(const Matrix&);

	float Determinant(vector<vector<float> >&,int);
	void Calc_Inverse();

	vector<float> Vec_Mul(vector<float>&);
	vector<float> Inv_Vec_Mul(vector<float>&);

	void print();
	void print_Inv();

	Ray transform_inv(Ray &r);
	void transform_inv_transpose(vector<float> &v);
	
	private:
	 void Cofactor(int,int,vector<vector<float> >&,vector<vector<float> >&,int);
	 void Adjoint(vector<vector<float> > &,vector<vector<float> > &);
};