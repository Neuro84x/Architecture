#include <iostream>
#include <cmath>


using namespace std;


const int SIZE = 100;
const double e = 0.0001;


void printMartix(double A[][SIZE], int rows, int cols) {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			cout << A[i][j] << " ";
		}
		cout << endl;
	}
}

double max_in_rows(double A[][SIZE], int rows, int cols) {
	double a[SIZE] = {};
	double maxi = -100;

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			a[i] += A[i][j];
		}
	}

	for (int i = 0; i < rows; ++i) {
		if (a[i] > maxi) {
			maxi = a[i];
		}
	}


	return maxi;
}

double max_in_rows(double A[SIZE], int rows) {

	double maxi = -100;


	for (int i = 0; i < rows; ++i) {
		if (A[i] > maxi) {
			maxi = A[i];
		}
	}

	return maxi;
}

void MPI() {
	double A[SIZE][SIZE];	//исходная матрица
	double X[SIZE][SIZE];	//иксы

	//матрицы разбиения
	double E[SIZE][SIZE];
	double C[SIZE][SIZE];
	double B[SIZE];

	//матрица умножения
	double P[SIZE] = {};

	double normC;	//норма матрицы C[][]
	double normB;	//норма матрицы B[][]

	int rows = 3, cols = 4;	//размер матрицы
	int N;	//кол-во шагов


	//Ввод размера матрицы
	/*cout << "Enter the matrix size: ";
	cin >> rows >> cols;
	cols++;
	cout << endl;*/


	//Ввод матрицы
	cout << "Enter the matrix" << endl;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			cin >> A[i][j];
		}
	}


	//Приводим к удобному размеру для иттераций
	double p;
	for (int i = 0; i < rows; ++i) {
		p = A[i][i];
		for (int j = 0; j < cols; ++j) {
			A[i][j] /= p;
		}
	}

	printMartix(A, rows, cols);


	//Заполняем матрицу E[][] и C[][]
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols - 1; ++j) {
			if (i == j) {
				E[i][j] = 1;
				C[i][j] = 0;
			}
			else {
				E[i][j] = 0;
				C[i][j] = A[i][j];
			}
		}
	}


	//Заполняем матрицу B[][]
	for (int i = 0; i < rows; ++i) {
		B[i] = A[i][cols - 1];
	}


	//Выводим матрицы E[][] C[][] B[][]
	cout << endl << "Matrix E[][]:" << endl;
	printMartix(E, rows, cols - 1);

	cout << endl << "Matrix C[][]:" << endl;
	printMartix(C, rows, cols - 1);

	cout << endl << "Matrix B[][]" << endl;
	for (int i = 0; i < rows; ++i) {
		cout << B[i] << endl;
	}


	//Считаем нормы матриц
	normC = max_in_rows(C, rows, cols - 1);
	normB = max_in_rows(B, rows);



	cout << endl << "||C|| = " << normC << endl;
	cout << endl << "||B|| = " << normB << endl;

	if (normC < 1) {

		//Считаем кол-во шагов
		//N = ceil((log(((e * (1 - normC)))) / ((log(normC))))) + 1;
		N = ceil((log((e * (1 - normC)) / (normB))) / (log(normC))) + 1;
		cout << endl << "Number of itterations: " << N << endl;


		//Начальный вектор (нулевой) и X[1]
		for (int i = 0; i < rows; ++i) {
			X[0][i] = 0;
			X[1][i] = B[i];
		}


		////Иттерации
		//p = 0;
		//for (int i = 2; i < N; ++i) {
		//	for (int j = 0; j < rows; ++j) {
		//		for (int k = 0; k < cols - 1; ++k) {
		//			p = C[j][k] * X[i - 1][k];
		//			P[j] += p;
		//		}
		//		X[i][j] = B[j] - P[j];
		//	}
		//	for (int s = 0; s < rows; ++s) {
		//		P[s] = 0;
		//	}
		//}


		////Выводим все шаги
		//for (int i = 0; i < N; ++i) {
		//	cout << "N = " << i << endl;
		//	for (int j = 0; j < rows; ++j) {
		//		cout << "X" << j << " = " << X[i][j] << "   ";
		//	}
		//	cout << endl << endl;
		//}


		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				X[i][j] = 0;
				//X[1][i] = B[i];
			}
		}


		//Зейдель
		int index, k = 0, cap = 0;
		double cell = 0;
		k = 0;
		while (k < N) {
			if ((abs(abs(X[k][0])-abs(X[k-1][0]))) < e && (abs(abs(X[k][1]) - abs(X[k - 1][1]))) < e && (abs(abs(X[k][2]) - abs(X[k - 1][2]))) < e) {
				break;
			}
			for (int i = 0; i < rows; ++i) {
				index = cap;
				for (int j = 0; j < rows; ++j) {
					if (!X[k + 1][j]) {
						cell += C[i][j] * X[k][j];
					}
					else {
						if (index >= 0) {
							cell += C[i][j] * X[k + 1][j];
							index--;
						}
					}
				}
				X[k + 1][i] = B[i] - cell;
				cell = 0;
				cap++;
			}
			k++;
		}

		//Выводим все шаги
		for (int i = 0; i < k; ++i) {
			cout << "N = " << i << endl;
			for (int j = 0; j < rows; ++j) {
				cout << "X" << j << " = " << X[i][j] << "   ";
			}
			cout << endl << endl;
		}
	}
	else {
		cout << "There is no decision" << endl;
		return;
	}
}

int main() {

	MPI();

	return 0;
}