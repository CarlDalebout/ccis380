#include <GL/freeglut.h>
#include <iostream>
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    glVertex2i(0, 0);
    glVertex2i(100, 200);
    glVertex2i(200, 0);
    glVertex2i(200, 300);
    glEnd();

    glFlush();
}
int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("OpenGL!!!");

    glutDisplayFunc(display);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0f, 400.0f, 0.0f, 400.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glLineWidth(20.0f);

    glutMainLoop();

    return 0;
}
