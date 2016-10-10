#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cmath>

class Vector
{
  public:
    double x;
    double y;

    // constructors
    Vector()
    {
        Vector(0.0, 0.0);
    }

    Vector(double X, double Y)
    {

        this->x = X;
        this->y = Y;
    }

    /*************************************************/

    // vector addition
    Vector operator+(const Vector v)
    {

        return Vector(x + v.x,
                      y + v.y);
    }

    // vector subtraction
    Vector operator-(const Vector v)
    {

        return Vector(x - v.x,
                      y - v.y);
    }

    Vector operator*(const Vector v)
    {

        return Vector(x * v.x,
                      y * v.y);
    }

    // vector times scalar product (scale length of vector times argument)
    Vector operator*(const double s)
    {

        return Vector(x * s,
                      y * s);
    }

    Vector operator+(const double s)
    {

        return Vector(x + s,
                      y + s);
    }

    // vector divided by a scalar (divide length of vector by argument)
    Vector operator/(const double s)
    {

        return Vector(x / s,
                      y / s);
    }

    // dot product
    double dot(const Vector v)
    {

        return (x * v.x) + (y * v.y);
    }

    double length()
    {

        return std::sqrt(x * x + y * y);
    }
    void print()
    {

        std::cout << "( " << x << " " << y << " )" << std::endl;
    }
};

#endif