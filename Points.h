#ifndef MYLIBFORMATH_POINTS_H
#define MYLIBFORMATH_POINTS_H

#include <iostream>
#include <cmath>

class PointR3;

class PointR2{
protected:
    double _x, _y;
public:
    PointR2();
    PointR2(double x, double y);
    PointR2(const PointR2& other);
    explicit PointR2(const PointR3& other);
    PointR2(PointR2&& other) noexcept;
    ~PointR2();

    [[nodiscard]] double getX() const;
    [[nodiscard]] double getY() const;
    void setX(double x);
    void setY(double y);

    virtual void PrintPoint();

    PointR2 operator+(const PointR2& other);
    PointR2 operator-(const PointR2& other);
    PointR2 operator*(double scalar);
    PointR2& operator+=(const PointR2& other);
    PointR2& operator-=(const PointR2& other);
    PointR2& operator*=(double scalar);
    PointR2& operator=(const PointR2& other);
};

class PointR3 : public PointR2 {
private:
    double _z;
public:
    PointR3();
    PointR3(double x, double y, double z);
    PointR3(const PointR3& other);
    explicit PointR3(const PointR2& other);
    PointR3(PointR3&& other) noexcept;
    ~PointR3();

    [[nodiscard]] double getZ() const;
    void setZ(double z);

    void PrintPoint() override;

    PointR3 operator+(const PointR3& other);
    PointR3 operator-(const PointR3& other);
    PointR3 operator*(double scalar);
    PointR3& operator+=(const PointR3& other);
    PointR3& operator-=(const PointR3& other);
    PointR3& operator*=(double scalar);
    PointR3& operator=(const PointR3& other);
};

#endif //MYLIBFORMATH_POINTS_H
