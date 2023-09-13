#include <ctime>
#include <cstdlib>
#include <GL/freeglut.h>

GLfloat black[3] = {0.0f, 0.0f, 0.0f};

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3fv(black);
    glBegin(GL_POINTS);
    for (int i = 0; i < 1000; i++)
    {
    GLint x = rand() % 100;
    GLint p[2] = {x, x};
    glVertex2iv(p);
    }
    glEnd();
    glFlush();
}

int main(int argc, char ** argv)
{
    srand((unsigned int) time(NULL));
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("OpenGL!!!");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0f, 400.0f, 0.0f, 400.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
