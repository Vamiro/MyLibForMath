#include "Vectors.h"

VectorR2::VectorR2() : _x(0), _y(0), _length(0), _direction(0)  {

}

VectorR2::VectorR2(PointR2 point) : _x(point.getX()), _y(point.getY()) {
    CalcLength();
    CalcDirection();
}

VectorR2::VectorR2(double length, double direction) : _length(length), _direction(direction) {
    CalcCoords();
}

VectorR2::VectorR2(const VectorR2& other) : _x(other._x), _y(other._y), _length(other._length), _direction(other._direction) {}

VectorR2::VectorR2(VectorR2&& other) noexcept : _x(other._x), _y(other._y), _length(other._length), _direction(other._direction) {}

void VectorR2::CalcLength() {
    _length = sqrt(_x * _x + _y * _y);
}

void VectorR2::CalcCoords() {
    _x = _length * cosl(_direction);
    _y = _length * sinl(_direction);
}

void VectorR2::CalcDirection() {
    _direction = atan2l(_y, _x);
    if (_direction < 0) {
        _direction += 2 * std::numbers::pi;
    }
}

double VectorR2::getX() const {
    return _x;
}

double VectorR2::getY() const {
    return _y;
}

double VectorR2::getLength() const {
    return _length;
}

double VectorR2::getDirection() const {
    return _direction;
}

void VectorR2::setX(double x) {
    _x = x;
    CalcLength();
    CalcDirection();
}

void VectorR2::setY(double y) {
    _y = y;
    CalcLength();
    CalcDirection();
}

void VectorR2::setLength(double length) {
    _length = length;
    CalcCoords();
}

void VectorR2::setDirection(double direction) {
    _direction = direction;
    CalcCoords();
}

void VectorR2::PrintVector() {
    std::cout << "x = " << _x << '\t' << "y = " << _y << '\t' << "length = " << _length << '\t' <<
              "direction = " << _direction << '\t' << "angle = " << _direction * (180.0/std::numbers::pi) << std::endl;
}

void VectorR2::PrintVectorByBasis() {
    VectorR2 out = ApplyMatrix();
    std::cout << "x = " << out._x << '\t' << "y = " << out._y << '\t' << "length = " << out._length << '\t' <<
              "direction = " << out._direction << '\t' << "angle = " << out._direction * (180.0/std::numbers::pi) << std::endl;
}

Matrix VectorR2::IdentityMatrix() {
    Matrix identity(2, 2);
    identity(0,0) = 1; identity(0,1) = 0;
    identity(1,0) = 0; identity(1,1) = 1;
    return identity;
}

VectorR2 VectorR2::ApplyMatrix() {
    Matrix matrix = IdentityMatrix();

    if (!matrix.IsSquare() || matrix.Determinant() == 0) {
        throw std::invalid_argument("Matrix must be a 2x2 matrix and determinant != 0");
    }

    VectorR2 a;
    a.setX(matrix(0, 0));
    a.setY(matrix(0, 1));
    VectorR2 b;
    b.setX(matrix(1, 0));
    b.setY(matrix(1, 1));

    a *= _x;
    b *= _y;

    return VectorR2(a + b);
}

VectorR2 VectorR2::Normalize() {
    if (_length != 0.0) {
        return VectorR2(1.0, _direction);
    }
    return VectorR2();
}

VectorR2 VectorR2::CalculateNormal() {
    return VectorR2(-_y, _x);
}

VectorR2 VectorR2::SumVector(const VectorR2& other) {
    return VectorR2(PointR2( _x + other._x, _y + other._y));
}

VectorR2 VectorR2::SubVector(const VectorR2& other) {
    return VectorR2(PointR2(_x - other._x, _y - other._y));
}

double VectorR2::DotProduct(const VectorR2& other) {
    return _x * other._x + _y * other._y;
}

VectorR2 VectorR2::MulVector(double scalar) {
    return VectorR2(std::abs(_length * scalar), _direction + (scalar < 0 ? std::numbers::pi : 0));
}

VectorR2 VectorR2::DivVector(double scalar) {
    if (scalar != 0.0) {
        return VectorR2(std::abs(_length / scalar), _direction + (scalar < 0 ? std::numbers::pi : 0));
    }
    return VectorR2();
}

// Operator overloads

VectorR2 VectorR2::operator+(const VectorR2& other) {
    return SumVector(other);
}

VectorR2 VectorR2::operator-(const VectorR2& other) {
    return SubVector(other);
}

double VectorR2::operator*(const VectorR2& other) {
    return DotProduct(other);
}

VectorR2 VectorR2::operator*(double scalar) {
    return MulVector(scalar);
}

VectorR2 VectorR2::operator/(double scalar) {
    return DivVector(scalar);
}

VectorR2& VectorR2::operator+=(const VectorR2& other) {
    *this = *this + other;
    return *this;
}

VectorR2& VectorR2::operator-=(const VectorR2& other) {
    *this = *this - other;
    return *this;
}

VectorR2& VectorR2::operator*=(double scalar) {
    *this = *this * scalar;
    return *this;
}
VectorR2& VectorR2::operator/=(double scalar) {
    *this = *this / scalar;
    return *this;
}

VectorR2& VectorR2::operator=(const VectorR2& other) {
    if (this == &other) {
        return *this;
    }
    _x = other._x;
    _y = other._y;
    _length = other._length;
    _direction = other._direction;
    return *this;
}