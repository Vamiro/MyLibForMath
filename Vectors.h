#ifndef MYLIBFORMATH_VECTORS_H
#define MYLIBFORMATH_VECTORS_H

#include "Points.h"
#include "Matrix.h"

class VectorR2{
private:
    double _x, _y;
    double _length;
    double _direction;
    void CalcLength();
    void CalcCoords();
    void CalcDirection();
public:
    VectorR2();
    explicit VectorR2(PointR2 point);
    VectorR2(double length, double direction);
    VectorR2(const VectorR2& other);
    VectorR2(VectorR2&& other) noexcept;

    [[nodiscard]] double getX() const;
    [[nodiscard]] double getY() const;
    [[nodiscard]] double getLength() const;
    [[nodiscard]] double getDirection() const;
    void setX(double x);
    void setY(double y);
    void setLength(double length);
    void setDirection(double direction);

    void PrintVector();
    void PrintVectorByBasis();
    Matrix IdentityMatrix();
    VectorR2 ApplyMatrix();
    VectorR2 Normalize();
    VectorR2 CalculateNormal();

    VectorR2 SumVector(const VectorR2& other);
    VectorR2 SubVector(const VectorR2& other);
    double DotProduct(const VectorR2& other);
    VectorR2 MulVector(double scalar);
    VectorR2 DivVector(double scalar);

    VectorR2 operator+(const VectorR2& other);
    VectorR2 operator-(const VectorR2& other);
    double operator*(const VectorR2& other);
    VectorR2 operator*(double scalar);
    VectorR2 operator/(double scalar);
    VectorR2& operator+=(const VectorR2& other);
    VectorR2& operator-=(const VectorR2& other);
    VectorR2& operator*=(double scalar);
    VectorR2& operator/=(double scalar);
    VectorR2& operator=(const VectorR2& other);

};

#endif //MYLIBFORMATH_VECTORS_H
