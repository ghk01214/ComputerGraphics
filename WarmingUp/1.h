#pragma once

class Matrix
{
public:
	Matrix();
	Matrix(int32 num);
	~Matrix();

	void Print();
	void Clear();
	void Reset();

	int32 GetDeterminant();
	int32 Recursive(Matrix* mat);
	void ChangeTo4x4();
	Matrix Transpose();

	Matrix operator+(Matrix& right);
	Matrix operator-(Matrix& right);
	Matrix operator*(Matrix& right);

private:
	std::vector<std::vector<int32>> matrix;
	int32 size;
};

void Add(Matrix& a, Matrix& b);
void Subtract(Matrix& a, Matrix& b);
void Multiply(Matrix& a, Matrix& b);
void Determinant3(Matrix& a, Matrix& b);
void Determinant4(Matrix& a, Matrix& b);
void Transpose(Matrix& a, Matrix& b);
void Reset(Matrix& a, Matrix& b);
void run1();