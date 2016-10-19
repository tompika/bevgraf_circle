#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cmath>

class Vector
{
  public:
    double x;
    double y;

    
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

    
    Vector operator+(const Vector v)
    {

        return Vector(x + v.x,
                      y + v.y);
    }

    
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

    Vector operator/(const double s)
    {

        return Vector(x / s,
                      y / s);
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