#include "Points.h"

PointR3::PointR3() : PointR2(), _z(0.0) {}

PointR3::PointR3(double x, double y, double z) : PointR2(x, y), _z(z) {}

PointR3::PointR3(const PointR3& other) : PointR2(other), _z(other._z) {}

PointR3::PointR3(const PointR2& other) : PointR2(other), _z(0.0) {}

PointR3::PointR3(PointR3&& other) noexcept : PointR2(std::move(other)), _z(other._z) {}

PointR3::~PointR3() {}

double PointR3::getZ() const{
    return _z;
}

void PointR3::setZ(double z) {
    _z = z;
}

void PointR3::PrintPoint() {

    std::cout << _x << '\t' << _y << '\t' << _z << std::endl;
}


PointR3 PointR3::operator+(const PointR3 &other) {
    return PointR3(_x + other._x, _y + other._y, _z + other._z);
}

PointR3 PointR3::operator-(const PointR3 &other) {
    return PointR3(_x - other._x, _y - other._y, _z - other._z);
}

PointR3 PointR3::operator*(double scalar) {
    return PointR3(_x * scalar, _y * scalar, _z * scalar);
}

PointR3 &PointR3::operator+=(const PointR3 &other) {
    _x += other._x;
    _y += other._y;
    _z += other._z;
    return *this;
}

PointR3 &PointR3::operator-=(const PointR3 &other) {
    _x -= other._x;
    _y -= other._y;
    _z -= other._z;
    return *this;
}

PointR3 &PointR3::operator*=(double scalar) {
    _x *= scalar;
    _y *= scalar;
    _z *= scalar;
    return *this;
}

PointR3 &PointR3::operator=(const PointR3 &other) {
    if (this == &other) {
        return *this;
    }
    PointR2::operator=(other);
    _z = other._z;

    return *this;
}
