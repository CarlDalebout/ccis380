#include <iostream>
#include <cmath>
#include <vector>
#include <GL/freeglut.h>
#include "../../a/mygllib/gl2d.h"

void draw_E()
{
    //14 in total

    glColor3f(0, 0, 1);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex2f(200, 250);
    glVertex2f(0, 250);
    glVertex2f(200, 200);
    glVertex2f(0, 200);
    glVertex2f(50, 200);
    glVertex2f(0, 0);
    glVertex2f(50, 0);
    glVertex2f(50, 50);
    glVertex2f(200, 0);
    glVertex2f(200, 50);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    glVertex2f(200, 150);
    glVertex2f(50, 150);
    glVertex2f(200, 100);
    glVertex2f(50, 100);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(400, 400);
    glEnd();


    draw_E();

    glFlush();
}

int main()
{
    mygllib::init2d(400, 400);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}