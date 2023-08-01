#include "Matrix.h"


Matrix::Matrix() {
    _rows = 3;
    _columns = 3;
    InitMatrix();
}

Matrix::Matrix(int rows, int columns) : _rows(rows), _columns(columns) {
    InitMatrix();
}

Matrix::Matrix(const Matrix &other){
    _rows = other._rows;
    _columns = other._columns;
    InitMatrix();
    memcpy(*(_matrix), *(other._matrix), other._rows * other._columns * sizeof(double));
}

Matrix::Matrix(Matrix&& other) noexcept : _rows(other._rows), _columns(other._columns), _matrix(other._matrix) {
    other._rows = 0;
    other._columns = 0;
    other._matrix = nullptr;
}

Matrix::~Matrix() {
    DeleteMatrix();
}

void Matrix::InitMatrix() {
    if(_rows <= 0 || _columns <= 0){
        throw std::out_of_range("Not valid size for matrix");
    }

    double *_pm;

    try {
        _matrix = new double *[_rows]();
        _pm = new double[_columns * _rows]();
    } catch (const std::exception& e) {
        delete [] _matrix;
        throw e;
    }

    for (int i = 0; i < _rows; ++i) {
        _matrix[i] = &_pm[i * _columns];
    }
}

void Matrix::DeleteMatrix() {
    if (_matrix) {
        delete[] _matrix[0];
        delete[] _matrix;
        _matrix = nullptr;
    }
}

int Matrix::GetRows() const{
    return _rows;
}

void Matrix::SetRows(int rows) {
    Matrix newMatrix(rows, _columns);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < _columns; ++j) {
            if(i < _rows) {
                newMatrix(i, j) = (*this)(i, j);
            }
        }
    }
    (*this) = newMatrix;
}

int Matrix::GetColumns() const{
    return _columns;
}

void Matrix::SetColumns(int columns) {
    Matrix newMatrix(_rows, columns);
    for (int i = 0; i < _rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if(j < _columns) {
                newMatrix(i, j) = (*this)(i, j);
            }
        }
    }
    (*this) = newMatrix;
}

bool Matrix::IsSquare() const {
    return _rows == _columns;
}

bool Matrix::EqualSize(const Matrix &other) {
    if(_rows == other._rows && _columns == other._columns){
        return true;
    }
    else {
        return false;
    }
}

void Matrix::PrintMatrix() const{
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _columns; j++) {
            std::cout << (*this)(i, j) << "\t";
        }
        std::cout << std::endl;
    }
}

bool Matrix::EqualMatrix(const Matrix &other) {
    if(!EqualSize(other)){
        throw std::invalid_argument("Matrix dimensions do not match for comparing.");
    }
    for (int i = 0; i < _rows; ++i) {
        for (int j = 0; j < _columns; ++j) {
            if(_matrix[i][j] != other._matrix[i][j]){
                return false;
            }
        }
    }
    return true;
}


void Matrix::SumMatrix(const Matrix &other) {
    if (!EqualSize(other)) {
        throw std::invalid_argument("Matrix dimensions do not match for addition.");
    }

    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _columns; j++) {
            (*this)(i, j) +=  other(i, j);
        }
    }
}

void Matrix::SubMatrix(const Matrix &other) {
    if (!EqualSize(other)) {
        throw std::invalid_argument("Matrix dimensions do not match for addition.");
    }

    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _columns; j++) {
            (*this)(i, j) -=  other(i, j);
        }
    }
}

void Matrix::MultiplyNumber(const double num) {
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _columns; j++) {
            (*this)(i, j) *=  num;
        }
    }
}

void Matrix::MultiplyMatrix(const Matrix &other) {
    if(_columns != other._rows){
        throw std::invalid_argument("Matrix dimensions are not suitable for multiplying.");
    }

    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < other._columns; j++) {
            for (int k = 0; k < _columns; k++) {
                (*this)(i, k) *=  other(k, j);
            }
        }
    }
}

Matrix Matrix::Transpose() const {
    Matrix result(_columns, _rows);
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _columns; j++) {
            result(j, i) = (*this)(i, j);
        }
    }
    return result;
}


Matrix Matrix::GetMinor(int row, int col) {
    Matrix minor(_rows - 1, _columns - 1);
    int minorRow = 0;

    for (int i = 0; i < _rows; ++i) {
        if (i == row) continue;

        int minorCol = 0;
        for (int j = 0; j < _columns; ++j) {
            if (j == col) continue;
            minor(minorRow, minorCol) = (*this)(i, j);
            ++minorCol;
        }
        ++minorRow;
    }

    return minor;
}

double Matrix::Determinant() {
    if (!IsSquare()) {
        throw std::logic_error("Determinant calculation requires a square matrix.");
    }
    if (_rows == 0 && _columns == 0) {
        throw std::logic_error("Determinant is undefined for an empty matrix.");
    }

    if (_rows == 1) {
        return (*this)(0, 0);
    }
    else if (_rows == 2) {
        return (*this)(0, 0) * (*this)(1, 1) - (*this)(0, 1) * (*this)(1, 0);
    }
    else {
        double determinant = 0;
        for (int i = 0; i < _columns; i++) {
            Matrix submatrix = GetMinor(0, i); // Use the correct submatrix here
            determinant += (i % 2 == 0 ? 1 : -1) * (*this)(0, i) * submatrix.Determinant(); // Use submatrix.Determinant() here
        }
        return determinant;
    }
}

Matrix Matrix::CalcComplements() {
    if (!IsSquare()) {
        throw std::logic_error("Cofactor calculation requires a square matrix.");
    }

    Matrix complements(_rows, _columns);

    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _columns; j++) {
            Matrix minor = GetMinor(i, j);
            double minorDeterminant = minor.Determinant();

            double complement = pow(-1.0, i + j) * minorDeterminant;

            complements(i, j) = complement;
        }
    }

    return complements;
}

Matrix Matrix::InverseMatrix() {
    if (!IsSquare()) {
        throw std::logic_error("Inverse matrix calculation requires a square matrix.");
    }

    double determinant = Determinant();
    if (determinant == 0.0) {
        throw std::logic_error("The matrix is singular, and its inverse does not exist.");
    }
    //A^(-1) = (1 / det(A)) * adj(A)^(T)
    return CalcComplements().Transpose() * (1 / determinant);
}

Matrix Matrix::operator+(const Matrix &other) {
    Matrix result(*this);
    result.SumMatrix(other);
    return result;
}

Matrix Matrix::operator-(const Matrix &other) {
    Matrix result(*this);
    result.SubMatrix(other);
    return result;
}

Matrix Matrix::operator*(const double num) {
    Matrix result(*this);
    result.MultiplyNumber(num);
    return result;
}

Matrix Matrix::operator*(const Matrix &other) {
    Matrix result(*this);
    result.MultiplyMatrix(other);
    return result;
}

bool Matrix::operator==(const Matrix &other) {
    bool result = EqualMatrix(other);
    return result;
}

Matrix& Matrix::operator=(const Matrix &other) {
    DeleteMatrix();
    _rows = other._rows;
    _columns = other._columns;
    InitMatrix();
    memcpy(*(_matrix), *(other._matrix), other._rows * other._columns * sizeof(double));
    return (*this);
}

Matrix& Matrix::operator=(Matrix &&other) {
    DeleteMatrix();
    _rows = other._rows;
    _columns = other._columns;
    _matrix = other._matrix;
    other._rows = 0;
    other._columns = 0;
    other._matrix = nullptr;
    return (*this);
}

Matrix& Matrix::operator+=(const Matrix &other) {
    SumMatrix(other);
    return (*this);
}

Matrix& Matrix::operator-=(const Matrix &other) {
    SubMatrix(other);
    return (*this);
}

Matrix& Matrix::operator*=(const double num) {
    MultiplyNumber(num);
    return (*this);
}

Matrix& Matrix::operator*=(const Matrix &other) {
    MultiplyMatrix(other);
    return (*this);
}
double& Matrix::operator()(int row, int col) const{
    if (row >= _rows || col >= _columns) {
        throw std::out_of_range("Incorrect input, index is out of range");
    }
    return _matrix[row][col];
}

