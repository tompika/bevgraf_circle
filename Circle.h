#ifndef CIRCLE_H
#define CIRCLE_H

#include <iostream>
#include <math.h>
#include <time.h>

#include "Vector.h"
#include "Line.h"

#define PI 3.141592653589793

typedef struct point2d
{
    GLfloat x, y;
} POINT2D;

POINT2D initPoint2D( GLfloat x, GLfloat y )
{
    POINT2D P;
    P.x = x;
    P.y = y;
    return P;
}

class Circle {
    private:
  
    public:

        Vector center;
        Vector speedVector;
        GLdouble radius;
        int n;


    Circle(void){     
    };

    Circle(Vector _center, Vector _speedVector, GLdouble _radius, int _n){
        
       
        this->center = _center;
        this->speedVector = _speedVector;
        this->radius = _radius;
        this->n = _n;

        


    }

    void draw(){
      

        glLineWidth(1);
        glColor3f(0.0, 0.0, 0.0);
        
        //glBegin(GL_LINE_LOOP); 
        glBegin(GL_TRIANGLE_FAN);

        for (GLdouble t = 0; t <= 2 * PI; t += 0.01){

            glVertex2d(center.x + radius * cos(t), center.y + radius * sin(t));
        
        }

        glEnd();

     
    
    }

    void drawNszog()
    {

        
        glColor3f(1.0, 1.0, 1.0);

        POINT2D points [n];

        int i,j;
        GLfloat angle;

        if(n < 3)
            n = 3;
        
        glBegin(GL_LINE_LOOP);
        for(i = 0, angle = 0.0; i < n; i++, angle += 2.0 * PI / n)
        {
            glVertex2f(center.x + radius * cos(angle), center.y + radius * sin(angle));
            points[i] = initPoint2D(center.x + radius * cos(angle), center.y + radius * sin(angle)); 
            
        }
        glEnd();
        
        glBegin(GL_LINE_LOOP);
        for(i = 0; i<n; i++)
        {
                
                for( j = i ; j<n ; j++ ) {
                    glVertex2f(points[i].x, points[i].y);
                    glVertex2f(points[j].x, points[j].y);
                
                }
            }
            glEnd();
                
                
        
    
}

    void moveOneStep()
	{
        this->center = this->center + this->speedVector * 1;
    }

    double distanceFromLine(Line l){

        double normalLength = hypot(l.endPoint.x - l.startPoint.x, l.endPoint.y - l.startPoint.y);

        double distance = abs( (double)((center.x - l.startPoint.x) * (l.endPoint.y - l.startPoint.y) -
                                (center.y - l.startPoint.y) * (l.endPoint.x - l.startPoint.x)) / normalLength );
    return distance;

    }


};





#endif