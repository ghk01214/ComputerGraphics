#include "pch.h"
#include "1.h"

Matrix::Matrix() : matrix{ 4 }, size{ 3 }
{
	Reset();
}

Matrix::Matrix(int32 num) : matrix{ 4 }, size{ 3 }
{
	for (int32 i = 0; i < 4; ++i)
	{
		std::vector<int32> v(4, num);
		matrix[i] = v;
	}

	matrix[3][3] = 1;
}

Matrix::~Matrix()
{
}

void Matrix::Print()
{
	for (int32 i = 0; i < size; ++i)
	{
		std::cout << "┃ ";

		for (int32 j = 0; j < size; ++j)
		{
			std::cout << matrix[i][j] << " ";
		}

		std::cout << "┃\n";
	}
}

void Matrix::Clear()
{
	matrix.clear();
}

void Matrix::Reset()
{
	for (int32 i = 0; i < 4; ++i)
	{
		std::vector<int32> v{};
		v.resize(4);

		for (int32 j = 0; j < 4; ++j)
		{
			v[j] = uid_color(dre);
		}

		matrix[i] = v;
	}

	for (int32 i = 0; i < 4; ++i)
	{
		matrix[i][3] = 0;
		matrix[3][i] = 0;
	}

	matrix[3][3] = 1;
}

int32 Matrix::GetDeterminant()
{
	return Recursive(this);
}

int32 Matrix::Recursive(Matrix* mat)
{
	if (mat->matrix.size() == 2)
	{
		return (mat->matrix[0][0] * mat->matrix[1][1]) - (mat->matrix[1][0] * mat->matrix[0][1]);
	}

	int32 deter{};
	int32 sign{ 1 };

	for (int32 i = 0; i < mat->matrix[0].size(); ++i)
	{
		Matrix m{};
		m.Clear();

		for (int32 j = 1; j < mat->matrix.size(); ++j)
		{
			std::vector<int32> temp;

			for (int32 k = 0; k < mat->matrix[0].size(); ++k)
			{
				if (k != i)
					temp.push_back(mat->matrix[j][k]);
			}

			m.matrix.push_back(temp);
		}

		deter += mat->matrix[0][i] * sign * Recursive(&m);
		sign *= -1;
	}

	return deter;
}

void Matrix::ChangeTo4x4()
{
	size = 4;
}

Matrix Matrix::Transpose()
{
	Matrix m{ 0 };

	for (int32 i = 0; i < size; ++i)
	{
		for (int32 j = 0; j < size; ++j)
		{
			m.matrix[j][i] = matrix[i][j];
		}
	}

	return m;
}

Matrix Matrix::operator+(Matrix& right)
{
	Matrix m{};

	for (int32 i = 0; i < size; ++i)
	{
		for (int32 j = 0; j < size; ++j)
		{
			m.matrix[i][j] = matrix[i][j] + right.matrix[i][j];
		}
	}

	return m;
}

Matrix Matrix::operator-(Matrix& right)
{
	Matrix m{};

	for (int32 i = 0; i < size; ++i)
	{
		for (int32 j = 0; j < size; ++j)
		{
			m.matrix[i][j] = matrix[i][j] - right.matrix[i][j];
		}
	}

	return m;
}

Matrix Matrix::operator*(Matrix& right)
{
	Matrix m{ 0 };

	for (int32 i = 0; i < size; ++i)
	{
		for (int32 j = 0; j < size; ++j)
		{
			int32 sum{};

			for (int32 k = 0; k < size; ++k)
			{
				m.matrix[i][j] += matrix[i][k] * right.matrix[k][j];
			}
		}
	}

	return m;
}

void Add(Matrix& a, Matrix& b)
{
	Matrix sum{ a + b };

	std::cout << std::format("1번 행렬 : \n");
	a.Print();

	std::cout << std::format("2번 행렬 : \n");
	b.Print();

	std::cout << std::format("result : \n");
	sum.Print();
}

void Subtract(Matrix& a, Matrix& b)
{
	Matrix sub{ a - b };

	std::cout << std::format("1번 행렬 : \n");
	a.Print();

	std::cout << std::format("2번 행렬 : \n");
	b.Print();

	std::cout << std::format("result : \n");
	sub.Print();
}

void Multiply(Matrix& a, Matrix& b)
{
	Matrix mul{ a * b };

	std::cout << std::format("1번 행렬 : \n");
	a.Print();

	std::cout << std::format("2번 행렬 : \n");
	b.Print();

	std::cout << std::format("result : \n");
	mul.Print();
}

void Determinant3(Matrix& a, Matrix& b)
{
	std::cout << std::format("1번 행렬 : \n");
	a.Print();

	std::cout << std::format("2번 행렬 : \n");
	b.Print();

	std::cout << std::format("1번 행렬식 : {}\n", a.GetDeterminant());
	std::cout << std::format("2번 행렬식 : {}\n", b.GetDeterminant());
}

void Determinant4(Matrix& a, Matrix& b)
{
	a.ChangeTo4x4();
	b.ChangeTo4x4();

	std::cout << std::format("1번 행렬 : \n");
	a.Print();

	std::cout << std::format("2번 행렬 : \n");
	b.Print();

	std::cout << std::format("1번 행렬식 : {}\n", a.GetDeterminant());
	std::cout << std::format("2번 행렬식 : {}\n", b.GetDeterminant());
}

void Transpose(Matrix& a, Matrix& b)
{
	std::cout << std::format("1번 행렬 : \n");
	a.Print();

	std::cout << std::format("2번 행렬 : \n");
	b.Print();

	a = a.Transpose();
	b = b.Transpose();

	std::cout << std::format("1번 전치 행렬 : \n");
	a.Print();

	std::cout << std::format("2번 전치 행렬 : \n");
	b.Print();

	std::cout << std::format("1번 전치 행렬식 : {}\n", a.GetDeterminant());
	std::cout << std::format("2번 전치 행렬식 : {}\n", b.GetDeterminant());
}

void Reset(Matrix& a, Matrix& b)
{
	a.Reset();
	b.Reset();
}

void run1()
{
	bool end{ false };
	char command{};

	Matrix a{};
	Matrix b{};

	while (true)
	{
		std::cout << std::format("Command : ");
		std::cin >> command;

		switch (command)
		{
			case 'A': FALLTHROUGH
			case 'a':
			{
				Add(a, b);
			}
			break;
			case 'D': FALLTHROUGH
			case 'd':
			{
				Subtract(a, b);
			}
			break;
			case 'M': FALLTHROUGH
			case 'm':
			{
				Multiply(a, b);
			}
			break;
			case 'R': FALLTHROUGH
			case 'r':
			{
				Determinant3(a, b);
			}
			break;
			case 'T': FALLTHROUGH
			case 't':
			{
				Transpose(a, b);
			}
			break;
			case 'H': FALLTHROUGH
			case 'h':
			{
				Determinant4(a, b);
			}
			break;
			case 'S': FALLTHROUGH
			case 's':
			{
				Reset(a, b);
				std::cout << std::format("리셋 완료");
			}
			break;
			case 'Q': FALLTHROUGH
			case 'q':
			{
				std::cout << std::format("프로그램 종료\n");

				return;
			}
			break;
			default:
			{
				std::cout << std::format("잘못된 명령\n");
			}
		}

		std::cin.ignore();
		command = 0;

		std::system("pause");
		std::system("cls");
	}
}