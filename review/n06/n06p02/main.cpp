#include <GL/freeglut.h>
#include "../mygllib/gl2d.h"
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f); // red
    glVertex2f(0.0f, 0.0f);
    
    glColor3f(0.0f, 1.0f, 0.0f); // green
    glVertex2f(300.5f, 0.0f);
    
    glColor3f(0.0f, 0.0f, 1.0f); // blue
    glVertex2f(300.0f, 100.0f);
    
    glColor3f(1.0f, 0.0f, 0.0f); // red
    glVertex2f(200.0f, 200.0f);
    
    glColor3f(0.0f, 1.0f, 0.0f); // green
    glVertex2f(100.0f, 200.0f);
    
    glColor3f(0.0f, 0.0f, 1.0f); // blue
    glVertex2f(0.0f, 100.0f);
    
    glEnd();
    glFlush();
}

int main(int argc, char ** argv)
{
    mygllib::init2d();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
