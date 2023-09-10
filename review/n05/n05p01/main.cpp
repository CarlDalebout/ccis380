#include <GL/freeglut.h>

// float point0[] = {0, 0};
// float point1[] = {100, 100};
// float point2[] = {200, 0};
// float point3[] = {200, 300};
float points[4][2] = {{0,0}, {100, 100}, {200, 0}, {200, 300}};

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    glBegin(GL_LINES);
    glVertex2i(points[0][0], points[0][1]);
    glVertex2i(points[1][0], points[1][1]);
    glVertex2i(points[2][0], points[2][1]);
    glVertex2i(points[3][0], points[3][1]);
    glVertex2i(400, 0);
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
    
    glutMainLoop();

    return 0;
}
