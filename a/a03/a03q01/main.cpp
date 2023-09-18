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


void regular_polygon(float x, float y, float r, int num_points, float color_r = 1, float color_g = 0, float color_b = 0)
{
    glColor3f(color_r, color_g, color_b);
    for(float i = 0; i < 360; i += 360/num_points)
    {
        float rad = i * 0.01745;
        glVertex2f(r*cos(rad)+x, r*sin(rad)+y);
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0);
    glBegin(GL_LINE_LOOP);
    regular_polygon(100, 300, 50, 20);

    glEnd();
    glFlush();
}


int main()
{
    mygllib::init2d(900, 900);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
