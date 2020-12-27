#include <iostream>
#include <fstream>
using namespace std;
template<typename T>
class Matrix {
	T** arr;
	int cols;
	int rows;
public:
	Matrix(int r, int c) : rows(r), cols(c)
	{
		arr = new int* [rows];
		for (size_t i = 0; i < rows; i++)
		{
			arr[i] = new int[cols];
		}
	}
	int getRows()
	{
		return rows;
	}
	int getCols()
	{
		return rows;
	}
	T getElem(int row, int col)
	{
		return arr[row][col];
	}
	Matrix(ifstream& is)
	{
		is >> rows >> cols;
		arr = new T * [rows];
		for (size_t i = 0; i < rows; i++)
		{
			arr[i] = new T[cols];
		}
		for (size_t i = 0; i < rows; i++)
		{
			for (size_t j = 0; j < cols; j++)
			{
				is >> arr[i][j];
			}
		}
	}
	~Matrix()
	{
		for (size_t i = 0; i < rows; i++)
		{
			delete[]arr[i];
		}
		delete arr;
	}

	Matrix* add(Matrix* matrix1, Matrix* matrix2) {
		if ((rows != matrix1->rows) or (cols != matrix1->cols))
			return nullptr;
		if ((rows != matrix2->rows) or (cols != matrix2->cols))
			return nullptr;
		Matrix* mat = new Matrix(cols, rows);
		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < cols; j++) {
				//mat->arr[i][j] = this->arr[i][j] + matrix->arr[i][j];
				mat->arr[i][j] = this->arr[i][j] + matrix1->arr[i][j] + matrix2->arr[i][j];
			}
		}
		return mat;
	}

	Matrix* subtract() {

	}

	Matrix* multiply_m_to_m() {

	}

	Matrix* multiply_m_to_v() {

	}

	Matrix* operator+(Matrix* matrix)
	{
		if (rows != matrix->rows or cols != matrix->cols)
			return nullptr;
		Matrix* mat = new Matrix(cols, rows);
		for (size_t i = 0; i < rows; i++)
		{
			for (size_t j = 0; j < cols; j++)
			{
				mat->arr[i][j] = this->arr[i][j] + matrix->arr[i][j];
			}
		}
		return mat;
	}
	Matrix* operator-(Matrix* matrix)
	{
		if (rows != matrix->rows or cols != matrix->cols)
			return nullptr;
		Matrix* mat = new Matrix(cols, rows);
		for (size_t i = 0; i < rows; i++)
		{
			for (size_t j = 0; j < cols; j++)
			{
				mat->arr[i][j] = this->arr[i][j] - matrix->arr[i][j];
			}
		}
		return mat;
	}
	Matrix* operator*(int num)
	{
		Matrix* mat = new Matrix(cols, rows);
		for (size_t i = 0; i < rows; i++)
		{
			for (size_t j = 0; j < cols; j++)
			{
				mat->arr[i][j] = arr[i][j] * num;
			}
		}
		return mat;
	}
	Matrix* operator*(Matrix* matrix)
	{
		int sum;
		if (rows != matrix->cols)
			return nullptr;
		Matrix* mat = new Matrix(rows, cols);
		for (size_t i = 0; i < rows; i++)
		{
			for (size_t j = 0; j < cols; j++)
			{
				sum = 0;
				for (size_t k = 0; k < rows; k++)
				{
					sum += arr[i][k] * matrix->arr[k][j];
				}
				mat->arr[i][j] = sum;
			}
		}
		return mat;
	}
	Matrix* operator=(Matrix* matrix)
	{
		if (rows != matrix->rows or cols != matrix->cols)
			return nullptr;
		for (size_t i = 0; i < rows; i++)
		{
			for (size_t j = 0; j < cols; j++)
			{
				arr[i][j] = matrix->arr[i][j];
			}
		}
		return this;
	}
	bool operator==(Matrix* matrix)
	{
		if (rows != matrix->rows or cols != matrix->cols)
			return false;
		for (size_t i = 0; i < rows; i++)
		{
			for (size_t j = 0; j < cols; j++)
			{
				if (arr[i][j] != matrix->arr[i][j])
					return false;
			}
		}
		return true;
	}
	template<typename M>
	friend ostream& operator<<(ostream& os, Matrix* mat);
	template<typename S>
	friend ostream& operator<<(ostream& os, Matrix mat);
	template<typename R>
	friend R* Foo(Matrix<R>* mat);
};
template<typename S>
ostream& operator<<(ostream& os, Matrix<S> mat)
{
	int mRows = mat.getRows();
	int mCols = mat.getCols();
	os << mRows << " " << mCols << " ";
	for (size_t i = 0; i < mRows; i++)
	{
		for (size_t j = 0; j < mCols; j++)
		{
			os << mat.getElem(i, j) << " ";
		}
	}
	return os;
}
template<typename M>
ostream& operator<<(ostream& os, Matrix<M>* mat)
{
	int mRows = mat->getRows();
	int mCols = mat->getCols();
	for (size_t i = 0; i < mRows; i++)
	{
		for (size_t j = 0; j < mCols; j++)
		{
			os << mat->getElem(i, j) << " ";
		}
		os << endl;
	}
	return os;
}
template<typename R>
R* Foo(Matrix<R>* mat)
{
	int mRows = mat->getRows();
	int mCols = mat->getCols();
	int* arr = new int[mRows];
	int* arr2 = new int[mRows];
	for (size_t i = 0; i < mRows; i++)
	{
		arr[i] = i + 1;
	}
	int sum = 0;
	for (size_t i = 0; i < mRows; i++)
	{
		for (size_t j = 0; j < mCols; j++)
		{
			sum += mat->arr[i][j] * arr[j];
		}
		arr2[i] = sum;
		sum = 0;
	}
	return arr2;
}
int main()
{
	setlocale(0, "Russian");
	string str = "C:\\Users\\agush\\Desktop\\крс\\matrix1.txt";
	string str2 = "C:\\Users\\agush\\Desktop\\крс\\matrix2.txt";
	string str3 = "C:\\Users\\agush\\Desktop\\крс\\matrix3.txt";
	ifstream ifstr(str3);
	Matrix<int>* matrix1 = new Matrix<int>(ifstr);
	Matrix<int>* matrix2 = new Matrix<int>(ifstr);
	Matrix<int>* m = new Matrix<int>(ifstr);
	ifstr.close();
	cout << "Первая матрица" << endl;
	cout << matrix1 << endl;
	cout << "Вторая матрица" << endl;
	cout << matrix2 << endl;
	cout << "разница матриц" << endl;
	cout << (*matrix1 - matrix2) << endl;
	cout << "Сумма матриц" << endl;
	//cout << (*matrix1 + matrix2) << endl;
	m->add(matrix1, matrix2);
	cout << "умножение матрицы на число" << endl;
	cout << *matrix1 * 2 << endl;
	cout << "умножение матрицы на вектор" << endl;
	int* arr2 = Foo(matrix1);
	int x = matrix1->getRows();
	for (size_t i = 0; i < x; i++)
	{
		cout << arr2[i] << endl;
	}
	cout << endl;
	cout << "Произведение матриц" << endl;
	cout << *matrix1 * matrix2 << endl;
	cout << "Присвоение первой матрице значения второй:" << endl;
	matrix1 = matrix2;
	cout << matrix1 << endl;
	cout << "Равенство матриц:" << endl;
	cout << "Первая матрица и вторая: " << (*matrix1 == matrix2) << endl;
	cout << "Первая матрица и первая: " << (*matrix1 == matrix1) << "\n\n";
	ofstream ofstr(str2);
	ofstr << *matrix1; //Вывод матрицы в файл
	cout << "Матрица успешно записана по адресу " << str2 << endl;
	return 0;
}
