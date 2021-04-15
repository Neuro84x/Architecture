#include <iostream>


using namespace std;


const int SIZE = 10;


void printMartix(double A[][SIZE], int rows, int cols) {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			cout << A[i][j] << " ";
		}
		cout << endl;
	}
}

bool IsCorrect(double A[][SIZE], int rows, int cols) {

	if (rows != cols) {
		cout << "Неверный размер матрицы!" << endl;
		return false;
	}

	for (int i = 1; i < rows - 1; ++i) {
		if (abs(A[i][i]) < abs(A[i][i - 1]) + abs(A[i][i + 1])) {
			cout << "Не выполнено условие достаточности!" << endl;
			return false;
		}
	}

	if ((abs(A[0][0]) < abs(A[0][1])) || (abs(A[rows - 1][rows - 1]) < abs(A[rows - 1][rows - 2]))) {
		cout << "Не выполнены условие достаточности!" << endl;
		return false;
	}

	for (int i = 0; i < rows; ++i) {
		if (A[i][i] == 0) {
			cout << "Нулевые элементы на главной диагонали!" << endl;
			return false;
		}
	}

	return true;
}

int main() {
	setlocale(LC_ALL, "Russian");

	int i, n, k, rows = -1;
	double z;
	double A[SIZE][SIZE];
	double B[SIZE];
	double eps[SIZE];
	double X[SIZE];
	double et[SIZE];

	cout << "Введите размерность матрицы: ";
	cin >> rows;

	cout << "Введите матрицу A[][]: " << endl;
	for (i = 0; i < rows; i++)
		for (k = 0; k < rows; k++)
			cin >> A[i][k];

	cout << "Матрица A[][]:" << endl;
	for (i = 0; i < rows; i++)
	{
		for (k = 0; k < rows; k++)
			cout << A[i][k] << "\t ";
		cout << endl;
	}

	cout << "Введите матрицу B[][]: " << endl;
	for (i = 0; i < rows; i++)
		cin >> B[i];

	cout << "Матрица B[][]:" << endl;
	for (i = 0; i < rows; i++)
		cout << B[i] << endl;

	if (IsCorrect(A, rows, rows)) {
		n = rows - 1;
		eps[0] = -A[0][1] / A[0][0];
		et[0] = B[0] / A[0][0];

		for (i = 1; i < n; i++)
		{
			z = A[i][i] + A[i][i - 1] * eps[i - 1];
			eps[i] = -A[i][i + 1] / z;
			et[i] = (B[i] - A[i][i - 1] * et[i - 1]) / z;
		}

		X[n] = (B[n] - A[n][n - 1] * et[n - 1]) / (A[n][n] + A[n][n - 1] * eps[n - 1]);

		for (i = n - 1; i >= 0; i--)
			X[i] = eps[i] * X[i + 1] + et[i];

		cout << "Матрица X[]:" << endl;
		for (i = 0; i < rows; i++)
			cout << X[i] << endl;
		return 0;

	}
	else {
		return 0;
	}
}