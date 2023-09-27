#include <cstring>
#include <GL/freeglut.h>
#include "gl2d.h"
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(0.0f, 0.0f, 1.0f);
    glRasterPos2i(200, 200);
    char s[] = "hello world 1.235";
    
    for (unsigned int i = 0; i < strlen(s); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
    }
    
    glFlush();
}

int main(int argc, char ** argv)
{
    mygllib::init2d();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}