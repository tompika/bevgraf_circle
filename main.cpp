#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <vector>

#include "Circle.h"
#include "Line.h"
#include "Vector.h"


#define PI 3.141592653589793

GLsizei winWidth = 800, winHeight = 600;

GLint keyStates[256];

GLfloat delta = 1;

GLint radius = 20;
GLint radiusPow2 = radius * 2;

/*
GLint lineHor_x0 = 0;
GLint lineHor_y0 = winHeight / 2;

GLint lineHor_x1 = winWidth;
GLint lineHor_y1 = winHeight / 2;

GLint line2Ver_x0 = winWidth / 2;
GLint line2Ver_y0 = 0;

GLint line2Ver_x1 = winWidth / 2;
GLint line2Ver_y1 = winHeight;*/

Vector p1, p2, p3, p4;

Line horLine;
Line verLine;

std::vector<Circle> allCicrle;

double rand(double fMin, double fMax);


void init( ) {
    glClearColor ( 1.0, 1.0, 1.0, 0.0 );
    glMatrixMode ( GL_PROJECTION );
    gluOrtho2D ( 0.0, winWidth, 0.0, winHeight );
    glShadeModel ( GL_FLAT );

    p1.x = 0;
    p1.y = (double)winHeight/2;

    //std::cout << "Horline vec length: " <<  p1.length() << std::endl;

    p2.x = (double)winWidth;
    p2.y = (double)winHeight/2;

    p3.x = winWidth / 2;
    p3.y = 0;

    p4.x = winWidth / 2;
    p4.y = winHeight;
    
    horLine = Line(p1, p2, 1);
    verLine = Line(p3, p4, 1);

}



void drawLine(){

    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(3);
  
    glBegin(GL_LINES);

        glVertex2d(horLine.startPoint.x, horLine.startPoint.y);
        glVertex2d(horLine.endPoint.x, horLine.endPoint.y);
        glVertex2d(verLine.startPoint.x, verLine.startPoint.y);
        glVertex2d(verLine.endPoint.x, verLine.endPoint.y);

    glEnd();


}

void keyPressed (unsigned char key, int x, int y) {
    keyStates[key] = 1;
    
}

void keyUp (unsigned char key, int x, int y) {
    keyStates[key] = 0;
    
}

void keyOperations ( ) {
    
    if (keyStates['a']) {

            verLine.startPoint.x    -= delta;
            verLine.endPoint.x      += delta;
        
    }
    
    if (keyStates['d']) {

            verLine.startPoint.x    += delta;
            verLine.endPoint.x      -= delta;

    }

    if (keyStates['s']) {	
        
            horLine.startPoint.y    -= delta;
            horLine.endPoint.y      += delta;
    }
    
    if (keyStates['w']) {
        
            horLine.startPoint.y    += delta;
            horLine.endPoint.y      -= delta;
    }


    glutPostRedisplay( );
}


void display( )
{

    keyOperations();
    glClear(GL_COLOR_BUFFER_BIT);
   
   

   

    glColor3f(0.000, 1.000, 0.000);
    glPointSize(4);
    glBegin(GL_POINTS);
        for( int i = 0; i<= winWidth; i+=8)
            for( int j = 0; j<= winHeight ; j+=8)
                glVertex2i(i, j);


    glEnd();

    for(int i=0; i<allCicrle.size(); i++)
    {
        allCicrle[i].draw();
        allCicrle[i].drawNszog();
    }

    drawLine();
   
   
    glutSwapBuffers();
}



void update( int n )
{  

   for(int i=0; i<allCicrle.size(); i++){
        allCicrle[i].moveOneStep();


        if ( allCicrle[i].center.x > winWidth - radius ||  allCicrle[i].center.x < radius )
            allCicrle[i].speedVector.x = allCicrle[i].speedVector.x * -1.0;
        
        if ( allCicrle[i].center.y > winHeight - radius ||  allCicrle[i].center.y < radius ) 
            allCicrle[i].speedVector.y = allCicrle[i].speedVector.y * -1.0;
        

 
        
        //std::cout << allCicrle[i].distanceFromLine(horLine) << std::endl;
        double horDst = allCicrle[i].distanceFromLine(horLine);
        double verDst = allCicrle[i].distanceFromLine(verLine);  

        if(horDst < radius || verDst < radius) {
            
            //std::cout << " -- " <<  allCicrle[i].distanceFromLine(horLine) << std::endl;
            double Rx, Ry;
            Vector cirSpedVec;
            cirSpedVec.x = allCicrle[i].speedVector.x;
            cirSpedVec.y = allCicrle[i].speedVector.y;

            if( horDst < radius)
            {
                Vector norm;
                norm = horLine.normal;
                /*
                I : A becsapódó labda sebességvektora. 
                (Persze tudjuk, hogy ez csak egy rövidítés! Odaképzeljük, hogy ez valójában egy x és y koordinátákkal rendelkező számpáros.)

                N : Az ütközési pontban vett felület normálisa. 
                (Egy olyan egységnyi hosszúságú vektor, ami az adott felületre az adott pontban merőleges.)*/

                Rx =  - (cirSpedVec.x) - 2 * ((cirSpedVec.x * norm.x + cirSpedVec.y * norm.y) / norm.length())* norm.x;
                Ry =  - (cirSpedVec.y) - 2 * ((cirSpedVec.x * norm.x + cirSpedVec.y * norm.y) / norm.length())* norm.y;


            }
            if( verDst < radius){
                Vector norm;
                norm = verLine.normal;

                Rx =  - (cirSpedVec.x) - 2 * ((cirSpedVec.x * norm.x + cirSpedVec.y * norm.y) / norm.length())* norm.x;
                Ry =  - (cirSpedVec.y) - 2 * ((cirSpedVec.x * norm.x + cirSpedVec.y * norm.y) / norm.length())* norm.y;

            }

            allCicrle[i].speedVector.x = Rx;
            allCicrle[i].speedVector.y = Ry;
        
        }
    
   }  

   glutPostRedisplay( );

   glutTimerFunc( 5, update, 0 );

}




void processMouse( GLint button, GLint action, GLint xMouse , GLint yMouse ) {
    
    if ( button == GLUT_LEFT_BUTTON && action == GLUT_DOWN )
    {
        GLdouble randX = rand( -2, 2 );
		GLdouble randY = rand( -2, 2 );

        int randNum = rand()%(10 - 3 + 1) + 3;
        
      
        

        //std::cout << randX << " " << randY << std::endl;
        //std::cout << xMouse << " " << winHeight - yMouse << std::endl;
        Vector pos;
        pos.x = xMouse;
        pos.y =  winHeight - yMouse;


        Vector speed;
        speed.x = randX;
        speed.y = randY;

        allCicrle.push_back( Circle(pos, 
                                    speed, 
                                    radius,
                                    randNum));

    }

    if ( button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN){
         double d;
         double temp = winHeight - yMouse;

         for(int i = 0; i<allCicrle.size(); i++){
             d =  sqrt(     pow( (xMouse - allCicrle[i].center.x ), 2 ) 
                        +   pow( temp -  allCicrle[i].center.y ,    2 ) 
                        ) ;
                        
                  
                        if ( d < radius ){
                        allCicrle.erase( allCicrle.begin() + i );
                        }
         }
        
    }

}


int main(int argc, char** argv)
{
    srand(time(NULL));

    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );

    glutInitWindowSize( winWidth, winHeight );
    glutInitWindowPosition ( 0, 100 );

    glutCreateWindow( argv[ 0 ] );
    init( );

    glutDisplayFunc( display );
   
    glutMouseFunc( processMouse );
    glutKeyboardFunc(keyPressed);
    glutKeyboardUpFunc(keyUp);
   
    glutTimerFunc( 5, update, 0 );
   
    glutMainLoop( );
    return 0;
}


double rand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
};