#include <ctime>
#include <cstdlib>
#include "gl2d.h"

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < 1000; i++)
    {
        glVertex2i(rand() % 100, rand() % 100);
    }
    glEnd();
    glFlush();
}

int main(int argc, char ** argv)
{
    srand((unsigned int) time(NULL));
    mygllib::init2d();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
