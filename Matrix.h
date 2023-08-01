#ifndef MYLIBFORMATH_MATRIX_H
#define MYLIBFORMATH_MATRIX_H

#include <iostream>
#include <cmath>
#include <cstring>

class Matrix{
private:
    int _rows, _columns;
    double **_matrix;
    void InitMatrix();
    void DeleteMatrix();
    Matrix GetMinor(int row, int col);
public:
    Matrix();
    Matrix(int rows, int columns);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other) noexcept ;
    ~Matrix();

    void SetRows(int rows);
    void SetColumns(int columns);
    [[nodiscard]] int GetRows() const;
    [[nodiscard]] int GetColumns() const;
    [[nodiscard]] bool IsSquare() const;
    bool EqualSize(const Matrix& other);

    void PrintMatrix() const;
    bool EqualMatrix(const Matrix& other);
    void SumMatrix(const Matrix& other);
    void SubMatrix(const Matrix& other);
    void MultiplyNumber(double num);
    void MultiplyMatrix(const Matrix& other);
    Matrix Transpose() const;
    Matrix CalcComplements();
    double Determinant();
    Matrix InverseMatrix();


    Matrix operator+(const Matrix& other);
    Matrix operator-(const Matrix& other);
    Matrix operator*(const double num);
    Matrix operator*(const Matrix& other);
    bool operator==(const Matrix& other);
    Matrix& operator=(const Matrix& other);
    Matrix& operator=(Matrix&& other);
    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(const double num);
    Matrix& operator*=(const Matrix& other);
    double& operator() (int row, int col) const;
};

#endif //MYLIBFORMATH_MATRIX_H
