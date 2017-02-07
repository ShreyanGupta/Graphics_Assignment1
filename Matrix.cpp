#include "Matrix.h"
#include "Ray.h"

Matrix::Matrix()
{
	t = vector<vector<float> > (4, vector<float> (4,0));
	t_1 = vector<vector<float> > (4, vector<float> (4,0));
	for (int i = 0; i < 4; i++)
		t[i][i] = 1;
}

Matrix::Matrix(float a00, float a01, float a02, float a03, float a10, float a11, float a12, float a13, float a20, float a21, float a22, float a23, float a30, float a31, float a32, float a33)
{
	t = vector<vector<float> > (4, vector<float> (4,0));
	t[0][0] = a00;
	t[0][1] = a01;
	t[0][2] = a02;
	t[0][3] = a03;
	t[1][0] = a10;
	t[1][1] = a11;
	t[1][2] = a12;
	t[1][3] = a13;
	t[2][0] = a20;
	t[2][1] = a21;
	t[2][2] = a22;
	t[2][3] = a23;
	t[3][0] = a30;
	t[3][1] = a31;
	t[3][2] = a32;
	t[3][3] = a33;
	t_1 = vector<vector<float> > (4, vector<float> (4,0));	
}

void Matrix::Cofactor(int p, int q, vector<vector<float> >& temp, vector<vector<float> >& x,int n)
{
	int i = 0, j = 0;
	for (int row = 0; row < n; row++)
		for (int col = 0; col < n; col++)
		{
			if (row != p && col != q)
			{
				temp[i][j++] = x[row][col];
				if (j == n-1)
				{
					j = 0;
					i++;
				}
			}
		}
}

float Matrix::Determinant(std::vector<std::vector<float> > &m,int n)
{
	float D = 0;
	if (n == 1)
		return m[0][0];
	vector<vector<float> > temp (4, vector<float> (4,0));
	int sign = 1;
	for (int f = 0; f < n; f++)
	{
		Cofactor(0,f,temp,m,n);
		D += (sign * m[0][f] * Determinant(temp,n-1));
		sign = -sign;
	}
	return D;
}

void Matrix::Adjoint(vector<vector<float> >&x, vector<vector<float> > &adj)
{
	int sign = 1;
	vector<vector<float> > temp (4, vector<float> (4,0));
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			Cofactor(i,j,temp,x,4);
			sign = ((((i+j)%2) == 0) ? 1 : -1);
			adj[j][i] = sign * Determinant(temp,3);
		}
}

void Matrix::Calc_Inverse()
{
	float det = Determinant(t,4);
	// cout << "det is : " << det << endl;
	if (det < 0.000001 && det > -0.000001)
	{
		cout << "SINGULAR! \n";
		return;
	}
	vector<vector<float> > adj (4, vector<float> (4,0));
	Adjoint(t,adj);
	// cout << "ADJ --------------- \n";
	// for (int i = 0; i < 4; i++)
	// 	for (int j = 0; j < 4; j++)
	// 		cout << adj[i][j] << " ";
	// cout << "--------------\n";

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			t_1[i][j] = adj[i][j]/float(det);
}

Matrix Matrix::operator*(const Matrix& m)
{
	Matrix ans (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			for (int k = 0; k < 4; k++)
				ans.t[i][j] += t[i][k]*m.t[k][j];
	return ans;
}

Matrix& Matrix::operator*=(const Matrix& m)
{
	Matrix ans = (*this)*m;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			this->t[i][j] = ans.t[i][j];
	return *this;
}

vector<float> Matrix::Vec_Mul(vector<float> &v)
{
	// v : length = 4.
	vector<float> ans(4,0);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			ans[i] += v[j]*t[j][i];
	return ans;
}

vector<float> Matrix::Inv_Vec_Mul(vector<float> &v)
{
	// v : length = 4.
	vector<float> ans(4,0);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			ans[i] += v[j]*t_1[j][i];
	return ans;
}

void Matrix::print()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			cout << t[i][j] << " ";
		cout << "\n";		
	}
}

void Matrix::print_Inv()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			cout << t_1[i][j] << " ";
		cout << "\n";				
	}
}

Ray Matrix::transform_inv(Ray &r){
	auto d = r.get_d();
	auto p = r.get_p();
	for(int i=0; i<3; ++i) p[i] -= t[3][i];
	vector<float> new_d(d);
	vector<float> new_p(p);
	// print_Inv();
	for(int i=0; i<3; ++i){
		new_p[i] = p[0]*t_1[0][i] + p[1]*t_1[1][i] + p[2]*t_1[2][i];
		new_d[i] = d[0]*t_1[0][i] + d[1]*t_1[1][i] + d[2]*t_1[2][i];
	}
	return Ray(new_d, new_p);
}

vector<float> Matrix::transform_inv_transpose(vector<float> v){
	vector<float> new_v(4,1);
	for(int i=0; i<3; ++i){
		new_v[i] = v[0]*t_1[i][0] + v[1]*t_1[i][1] + v[2]*t_1[i][2];
	}
	return new_v;
}


