#include <iostream>
#include <cmath>
#include <vector>
#include <GL/freeglut.h>
#include "../../mygllib/gl2d.h"

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

void arc(float x, float y, float r, int num_points,
         float start_angle = 0.0f,
         float end_angle = 2 * 3.14159)
{
    glBegin(GL_LINE_STRIP);
    glVertex2f(r*cos(start_angle)+x, r*sin(start_angle)+y);

    glColor3f(0, 1, 0);
    if(start_angle <= end_angle)
        for(float i = start_angle; i <= end_angle; i += end_angle/num_points)
        {
            glVertex2f(r*cos(i)+x, r*sin(i)+y);
        }
    else
        for(float i = end_angle; i <= start_angle; i += start_angle/num_points)
        {
            glVertex2f(r*cos(i)+x, r*sin(i)+y); 
        }
    
    glEnd();
}

void star(float x, float y, float r, int num_points = 5)
{
    glBegin(GL_LINE_LOOP);
    float rad = 0;
    glVertex2f(r*cos(rad)+x, r*sin(rad)+y);
    for(int i = 0; i < num_points-1; ++i)
    {
        //360 degree is 6.282 rad
         rad += (4 *3.14159 )/(num_points);
         glVertex2f(r*cos(rad)+x, r*sin(rad)+y);
    }

    glEnd();
}

void fixedstar(float x, float y, float r, int num_points = 5)
{
    glBegin(GL_LINE_LOOP);
    float rad = 3.14159/2;
    glVertex2f(r*cos(rad)+x, r*sin(rad)+y);
    for(int i = 0; i < num_points-1; ++i)
    {
        //360 degree is 6.282 rad
         rad += (4 *3.14159 )/(num_points);
         glVertex2f(r*cos(rad)+x, r*sin(rad)+y);
    }

    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(1, 0, 0);
    star(200, 200, 50);
    glFlush();
}


int main()
{
    mygllib::init2d(900, 900);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
