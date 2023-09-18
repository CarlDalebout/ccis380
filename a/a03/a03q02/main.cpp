#include <iostream>
#include <cmath>
#include <vector>
#include <GL/freeglut.h>
#include "../mygllib/gl2d.h"

struct point
{
    float x;
    float y;
};


void regular_polygon(float x, float y, float r, int num_points)
{
    glBegin(GL_LINE_LOOP);
    // glColor3f(color_r, color_g, color_b);
    for(float i = 0; i < 360; i += 360/num_points)
    {
        float rad = i * 0.01745;
        glVertex2f(r*cos(rad)+x, r*sin(rad)+y);
    }
    glEnd();
}

void circle(float x, float y, float r, int num_points=-1)
{
    
    if(num_points == -1)
        regular_polygon(x, y, r, 30);
    else 
        regular_polygon(x, y, r, num_points);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0);
    circle(100, 300, 50, 4);
    glColor3f(0, 0, 1);
    circle(300, 300, 50, 100);
    glColor3f(0, 1, 0);
    circle(100, 100, 50);



    glFlush();
}


int main()
{
    mygllib::init2d(900, 900);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
