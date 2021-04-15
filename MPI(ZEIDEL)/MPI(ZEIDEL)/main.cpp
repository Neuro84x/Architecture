#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#define _CRT_SECURE_NO_WARNINGS

void printVector(std::vector<std::vector<double>>& arr, double b[]) {
    for (int i = 0; i < arr.size(); ++i) {
        for (int j = 0; j < arr[0].size(); ++j) {
            printf("%0.2lf\t", arr[i][j]);
        }
        printf("| %0.2lf\t", b[i]);
        std::cout << "\n";
    }
    std::cout << "\n";
}

int main() {
    setlocale(LC_ALL, "Russian");
    const int n = 3;
    //std::cout << "Размер матрицы: ";
    //std::cin >> n;
    std::vector<std::vector<double>> arr(n, std::vector<double>(n));
    double B[n], C[n][n], E[n][n], cell, foundMaxInC[n];

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double k;
            std::cout << "[" << i << "][" << j << "] = ";
            scanf_s("%lf", &k);
            arr[i][j] = k;
        }
        double k;
        std::cout << "b[" << i << "] = ";
        scanf_s("%lf", &k);
        B[i] = k;
    }

    printVector(arr, B);

    for (int i = 0; i < n; ++i) {
        double k = arr[i][i];
        for (int j = 0; j < n; ++j) {
            arr[i][j] /= k;
        }
        B[i] /= k;
    }

    std::cout << "Матрица А и В после деления на диагональные элементы\n";
    printVector(arr, B);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j == i) {
                E[i][j] = 1;
                C[i][j] = 0;
            }
            else {
                E[i][j] = 0;
                C[i][j] = arr[i][j];
            }
            foundMaxInC[i] += std::abs(C[i][j]);
        }
    }

    double* maxC = std::max_element(foundMaxInC, foundMaxInC + n);
    double* maxB = std::max_element(B, B + n);
    //int N = (int)((log((pow(10, -4) * (1 - *maxC)) / *maxB) / log(*maxC))) + 1;
    int N = ceil((log((pow(10, -4) * (1 - *maxC)) / (*maxB))) / (log(*maxC))) + 1;

    std::vector<std::vector<double>> X(N, std::vector<double>(n));

    for (int i = 0; i < X.size(); ++i)
        for (int j = 0; j < X[0].size(); ++j)
            X[i][j] = 0;

    std::cout << "\nМатрица B\n";
    for (int i = 0; i < n; ++i) {
        printf("%0.3lf", B[i]);
        std::cout << "\n";
    }

    std::cout << "\nМатрица C\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            printf("%0.3lf\t", C[i][j]);
        std::cout << "\n";
    }

    std::cout << "\nМатрица E\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            printf("%0.3lf\t", E[i][j]);
        std::cout << "\n";
    }

    std::cout << "\nМаксимальное в С: " << *maxC << "\n";
    std::cout << "Максимальное в В: " << *maxB << "\n\n";

    int index, k = 0, cap = 0;
    while (k < N - 1) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cell += C[i][j] * X[k][j];
            }
            X[k + 1][i] = B[i] - cell;
            cell = 0;
        }
        k++;
    }

    std::cout << "\nИксы [МПИ]\n";
    for (int i = 0; i < X.size(); ++i) {
        std::cout << "x(" << i << "): ";
        for (int j = 0; j < X[0].size(); ++j)
            printf("%0.8lf\t", X[i][j]);
        std::cout << "\n";
    }

    k = 0;
    while (k < N - 1) {
        for (int i = 0; i < n; ++i) {
            index = cap;
            for (int j = 0; j < n; ++j) {
                if (index >= 0) {
                    cell += C[i][j] * X[k + 1][j];
                    index--;
                }
                else
                    cell += C[i][j] * X[k][j];
            }
            X[k + 1][i] = B[i] - cell;
            cell = 0;
            cap++;
        }
        k++;
    }

    std::cout << "\nИксы [Зейдель]\n";
    for (int i = 0; i < X.size(); ++i) {
        std::cout << "x(" << i << "): ";
        for (int j = 0; j < X[0].size(); ++j)
            printf("%0.9lf\t", X[i][j]);
        std::cout << "\n";
    }
    printf("\nКоличество шагов: %d", N);
}
