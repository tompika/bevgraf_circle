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

    Line(){
        this->c = 1;
    }

    Line(Vector startPoint, Vector endPoint, double c){
        this->startPoint = startPoint;
        this->endPoint = endPoint;
        this->c = c;

        

        this->direction = endPoint - startPoint;
        direction.x = direction.x / direction.length();
        direction.y = direction.y / direction.length();
        this->normal = Vector( direction.y * -1.0, direction.x );


    }

    void print(){
        std::cout << "Line: " << std::endl;
        std::cout << "( " <<  startPoint.x << " " << startPoint.y << " )" <<  std::endl;
        std::cout << "( " << endPoint.x << " " << endPoint.y << " )" << std::endl;
        std::cout << "Direction:";
        direction.print();

        std::cout << "Normal: ";
        normal.print();
    }
};

#endif


