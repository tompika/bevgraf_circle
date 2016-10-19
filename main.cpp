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

GLfloat delta = 3;

GLint radius = 20;

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

void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, winWidth, 0.0, winHeight);
    glShadeModel(GL_FLAT);

    p1.x = 0;
    p1.y = winHeight / 2;



    p2.x = winWidth;
    p2.y = winHeight / 2;

    p3.x = winWidth / 2;
    p3.y = 0;

    p4.x = winWidth / 2;
    p4.y = winHeight;

    horLine = Line(p1, p2, 1);
    verLine = Line(p3, p4, 1);



}

void drawLine()
{

    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(3);

    glBegin(GL_LINES);

    glVertex2d(horLine.startPoint.x, horLine.startPoint.y);
    glVertex2d(horLine.endPoint.x, horLine.endPoint.y);
    glVertex2d(verLine.startPoint.x, verLine.startPoint.y);
    glVertex2d(verLine.endPoint.x, verLine.endPoint.y);

    

    glEnd();
}

void keyPressed(unsigned char key, int x, int y)
{
    keyStates[key] = 1;
}

void keyUp(unsigned char key, int x, int y)
{
    keyStates[key] = 0;
}

void keyOperations()
{

    if (keyStates['a'])
    {

        if( verLine.startPoint.x > 0){
        verLine.startPoint.x -= delta;
        verLine.endPoint.x += delta;

        verLine.refreshVectors();
        }
        //verLine.getNormalVector().print();
    }

    if (keyStates['d'])
    {

        if( verLine.startPoint.x < 800 ){
        verLine.startPoint.x += delta;
        verLine.endPoint.x -= delta;

        verLine.refreshVectors();
        }
        //verLine.getNormalVector().print();
    }

    if (keyStates['s'])
    {

        if(  horLine.startPoint.y > 0){
        horLine.startPoint.y -= delta;
        horLine.endPoint.y += delta;


        horLine.refreshVectors();
        }

        //horLine.getNormalVector().print();
    }

    if (keyStates['w'])
    {
        if( horLine.startPoint.y < 600 ){
        horLine.startPoint.y += delta;
        horLine.endPoint.y -= delta;

        horLine.refreshVectors();
        }
        //horLine.getNormalVector().print();
    }

    glutPostRedisplay();
}

void display()
{

    keyOperations();
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.000, 1.000, 0.000);
    glPointSize(4);
    glBegin(GL_POINTS);
    for (int i = 1; i <= winWidth; i += 10)
        for (int j = 1; j <= winHeight; j += 10)
        {

            

            //C = -Ax0 - By0

            //e: A x + By + C = 0
            

            GLdouble C,e, C2, e2;
            GLdouble A = horLine.getNormalVector().x; 
            GLdouble B = horLine.getNormalVector().y;

            GLdouble A2 = verLine.getNormalVector().x;
            GLdouble B2 = verLine.getNormalVector().y;
            
            GLdouble x0 = horLine.startPoint.x;
            GLdouble y0 = horLine.startPoint.y;

            GLdouble x02 = verLine.startPoint.x;
            GLdouble y02 = verLine.startPoint.y;

            
            C = -1*A * x0 - (B * y0);

            C2 = -1*A2 * x02 - (B * y02);
  
            e = (A * i) + (B * j) + C;


            e2 = (A2 * i) + (B2 * j) + C2;

             

            if ( e < 0 && e2 < 0)
                glColor3f(0.0, 1.0, 0.0);

            else if( e < 0 && e2 > 0)
                glColor3f(1.0, 0.0, 0.0);
            
            else if( e > 0 && e2 < 0)
                glColor3f(1.0, 0.0, 1.0); 
                
            else
                glColor3f(0.0, 0.0, 1.0);



            glVertex2i(i, j);
        }

    glEnd();

    for (int i = 0; i < allCicrle.size(); i++)
    {
        allCicrle[i].draw();
        allCicrle[i].drawNszog();
    }

    drawLine();

    glutSwapBuffers();
}

void update(int n)
{

    for (int i = 0; i < allCicrle.size(); i++)
    {
        allCicrle[i].moveOneStep();

        if (allCicrle[i].center.x > winWidth - radius || allCicrle[i].center.x < radius)
            allCicrle[i].speedVector.x = allCicrle[i].speedVector.x * -1.0;

        if (allCicrle[i].center.y > winHeight - radius || allCicrle[i].center.y < radius)
            allCicrle[i].speedVector.y = allCicrle[i].speedVector.y * -1.0;

        double horDst = allCicrle[i].distanceFromLine(horLine);
        double verDst = allCicrle[i].distanceFromLine(verLine);



        if (horDst < radius || verDst < radius)
        {

            double Rx, Ry;
            Vector cirSpedVec, norm;
            cirSpedVec.x = allCicrle[i].speedVector.x;
            cirSpedVec.y = allCicrle[i].speedVector.y;

            GLdouble x1, y1, x2, y2, ab;
            Vector a, b, bt;

            if (horDst < radius)
            {

                norm = horLine.getDirectionVector();

                x1 = cirSpedVec.x; //* -1;
                y1 = cirSpedVec.y; //* -1;

                b = cirSpedVec; //* -1;
                a = norm;

                x2 = norm.x;
                y2 = norm.y;

                ab = x1 * x2 + y1 * y2;

                // bt = -b + 2 * (<a, b> / ||a||^2) * a;

                Rx = (b.x) * -1 + 2 * (ab / (a.length() * a.length())) * a.x;
                Ry = (b.y) * -1 + 2 * (ab / (a.length() * a.length())) * a.y;
            }
            if (verDst < radius)
            {

                norm = verLine.getDirectionVector();

                x1 = cirSpedVec.x; // * -1;
                y1 = cirSpedVec.y; // * -1;

                b = cirSpedVec; //* -1;
                a = norm;

                x2 = norm.x;
                y2 = norm.y;

                ab = x1 * x2 + y1 * y2;

                // bt = -b + 2 * (<a, b> / ||a||^2) * a;

                Rx = (b.x) * -1 + 2 * (ab / (a.length() * a.length())) * a.x;
                Ry = (b.y) * -1 + 2 * (ab / (a.length() * a.length())) * a.y;
            }

            allCicrle[i].speedVector.x = Rx;
            allCicrle[i].speedVector.y = Ry;
        }
    }

    glutPostRedisplay();

    glutTimerFunc(5, update, 0);
}

void processMouse(GLint button, GLint action, GLint xMouse, GLint yMouse)
{

    if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
    {
        GLdouble randX = rand(-2, 2);
        GLdouble randY = rand(-2, 2);

        int randNum = rand() % (10 - 3 + 1) + 3;

        Vector pos;
        pos.x = xMouse;
        pos.y = winHeight - yMouse;

        Vector speed;
        speed.x = randX;
        speed.y = randY;

        allCicrle.push_back(Circle(pos,
                                   speed,
                                   radius,
                                   randNum));
    }

    if (button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN)
    {
        double d;
        double temp = winHeight - yMouse;

        for (int i = 0; i < allCicrle.size(); i++)
        {
            d = sqrt(pow((xMouse - allCicrle[i].center.x), 2) + pow(temp - allCicrle[i].center.y, 2));

            if (d < radius)
            {
                allCicrle.erase(allCicrle.begin() + i);
            }
        }
    }
}

int main(int argc, char **argv)
{
    srand(time(NULL));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(winWidth, winHeight);
    glutInitWindowPosition(0, 100);

    glutCreateWindow(argv[0]);
    init();

    glutDisplayFunc(display);

    glutMouseFunc(processMouse);
    glutKeyboardFunc(keyPressed);
    glutKeyboardUpFunc(keyUp);

    glutTimerFunc(5, update, 0);

    glutMainLoop();
    return 0;
}

double rand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
};