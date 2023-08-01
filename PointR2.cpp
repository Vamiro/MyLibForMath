#include "Points.h"

PointR2::PointR2() : _x(0.0), _y(0.0) {}

PointR2::PointR2(double x, double y) : _x(x), _y(y) {}

PointR2::PointR2(const PointR2& other) : _x(other._x), _y(other._y) {}

PointR2::PointR2(const PointR3 &other) {}

PointR2::PointR2(PointR2&& other) noexcept : _x(other._x), _y(other._y) {}

PointR2::~PointR2() {}

double PointR2::getX() const {
    return _x;
}

double PointR2::getY() const {
    return _y;
}

void PointR2::setX(double x) {
    _x = x;
}

void PointR2::setY(double y) {
    _y = y;
}

void PointR2::PrintPoint() {
    std::cout << _x << '\t' << _y << std::endl;
}

PointR2 PointR2::operator+(const PointR2& other) {
    return PointR2(_x + other._x, _y + other._y);
}

PointR2 PointR2::operator-(const PointR2& other) {
    return PointR2(_x - other._x, _y - other._y);
}

PointR2 PointR2::operator*(double scalar) {
    return PointR2(_x * scalar, _y * scalar);
}

PointR2& PointR2::operator+=(const PointR2& other){
    _x += other._x;
    _y += other._y;
    return *this;
}

PointR2& PointR2::operator-=(const PointR2& other){
    _x -= other._x;
    _y -= other._y;
    return *this;
}

PointR2& PointR2::operator*=(double scalar){
    _x *= scalar;
    _y *= scalar;
    return *this;
}


PointR2& PointR2::operator=(const PointR2& other) {
    if (this != &other) {
        _x = other._x;
        _y = other._y;
    }
    return *this;
}

