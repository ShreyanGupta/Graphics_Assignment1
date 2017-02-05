#include "Matrix.h"

Matrix::Matrix()
{
	t = vector<vector<float> > (4, vector<float> (4,0));
}

Matrix Matrix::Inverse()
{
	Matrix m; // the inverse
	return m;
}

Matrix Matrix::operator*(const Matrix& m)
{
	Matrix ans;
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

void Matrix::print()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			cout << t[i][j] << " ";
		cout << "\n";		
	}
}