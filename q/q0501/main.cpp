#include <iostream>
#include <cmath>
#include <vector>
#include <GL/freeglut.h>
#include "../../a/mygllib/gl2d.h"

const int WIN_W = 400;
const int WIN_H = 400;

void print_grid()
{

    glColor3f(0, 0, 0);
    float dr = WIN_W / 20;
    for(int i = 1; i <= 20; ++i)
    {
        glBegin(GL_LINES);
        glVertex2f(i * dr, 0);
        glVertex2f(i * dr, WIN_H);
        glEnd();
    }
    for(int i = 1; i <= 20; ++i)
    {
        glBegin(GL_LINES);
        glVertex2f(0, i * dr);
        glVertex2f(WIN_W , i * dr);
        glEnd();
    }
}

void print_blue()
{
    float dr = 0.125;
    glColor3f(0, 0, 1);
    glBegin(GL_LINES);
    for(int i = 0; i < WIN_W / 0.125; ++i)
    {
        glVertex2f((i * dr), (100 * sinf(0.1 * (i * dr)) + 200));
    }
    glEnd();
}

void print_red()
{
    float dr = 0.125;
    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
    for(int i = 0; i < WIN_W / 0.125; ++i)
    {
        glVertex2f((i * dr), (50 * cosf(0.06 * (i * dr)) + 70 * sin(0.02 * (i * dr)) + 250));
    }
    glEnd();
}

void print_green()
{
    // (220, 304.0492771125353183304663386541)
    // float slope = -2.2064
    glColor3f(0, 1, 0);
    glBegin(GL_LINES);
    for(int i = 1360; i < 2160; ++i)
    {
        glVertex2f((i * 0.125), (-2.2064 * (i * 0.125) + 709.10897));
    }
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    print_grid();
    print_blue();
    print_red();
    print_green();

    glFlush();
}

int main()
{
    mygllib::init2d(WIN_W, WIN_H);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
