#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cmath>

class Vector  
{
public:
	
    double x;
    double y;
    double z;


        // constructors
        Vector () 
        {
            Vector(0.0, 0.0, 0.0);
        
        }
        
        Vector (double _x, double _y){

            Vector(_x, _y, 0.0);
        }

        Vector (double X, double Y, double Z) {
           
            this->x = X; 
            this->y = Y; 
            this->z = Z;
       
        }

/*************************************************/

        // vector addition
        Vector operator+ (const Vector v)  {
            
            return Vector ( x + v.x, 
                            y + v.y, 
                            z + v.z);
        }

        // vector subtraction
        Vector operator- (const Vector v)  {

            return Vector ( x - v.x,
                            y - v.y, 
                            z - v.z);
        }

        Vector operator* (const Vector v)  {
        
            return Vector(  x * v.x, 
                            y * v.y, 
                            z * v.z);
        }

        // vector times scalar product (scale length of vector times argument)
        Vector operator* (const double s)  {
        
            return Vector ( x * s, 
                            y * s, 
                            z * s);
        }

        // vector divided by a scalar (divide length of vector by argument)
        Vector operator/ (const double s)  {
        
            return Vector ( x / s, 
                            y / s, 
                            z / s);
        }

        // dot product
        double dot (const Vector v)  {
        
            return (x * v.x) + (y * v.y) + (z * v.z);
        
        }

        double length(){
      
            return std::sqrt( x * x + y * y + z * z );
        }
        void print(){
         
            std::cout << "( " << x << " " << y << " " << z << " )" << std::endl;

        }
};

#endif