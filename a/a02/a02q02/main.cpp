#include <ctime>
#include <cstdlib>
#include <GL/freeglut.h>
#include <iostream>
#include "complex.h"
#include "../mygllib/gl2d.h"

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    glEnd();
    glFlush();
}

int main(int argc, char ** argv)
{   
    mygllib::init2d(900, 400);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}