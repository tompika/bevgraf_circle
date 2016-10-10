#ifndef LINE_H
#define LINE_H

#include "Vector.h"

class Line
{

  public:
    Vector startPoint;
    Vector endPoint;
    double c;

    Vector normal;
    Vector direction;

    Line()
    {
        this->c = 1;
    }

    Line(Vector startPoint, Vector endPoint, double c)
    {
        this->startPoint = startPoint;
        this->endPoint = endPoint;
        this->c = c;

        this->direction = endPoint - startPoint;
        //this->direction.x = direction.x / this->direction.length();
        //this->direction.y = direction.y / this->direction.length();
        Vector normal;
        normal.x = (this->direction.y == 0) ? 0 : this->direction.y * -1;
        normal.y = this->direction.x;

        this->normal = normal;
    }

    Vector getNormalVector()
    {

        this->direction = endPoint - startPoint;

        Vector normal;
        normal.x = (this->direction.y == 0) ? 0 : this->direction.y * -1;
        normal.y = this->direction.x;

        this->normal = normal;

        return this->normal;
    }

    Vector getDirectionVector()
    {

        this->direction = this->endPoint - this->startPoint;

        return this->direction;
    }

    void print()
    {
        std::cout << "Line: " << std::endl;
        std::cout << "( " << startPoint.x << " " << startPoint.y << " )" << std::endl;
        std::cout << "( " << endPoint.x << " " << endPoint.y << " )" << std::endl;
        std::cout << "Direction:";
        direction.print();

        std::cout << "Normal: ";
        normal.print();

        std::cout << std::endl
                  << std::endl;
    }
};

#endif
