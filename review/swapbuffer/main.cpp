#include <GL/freeglut.h>
#include "gl2d.h"
float x0=50, y0=70, dx0=3, dy0=-1;
float x1=10, y1=20, dx1=-1, dy1=2;
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(x0, y0);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(x1, y1);
	glEnd();
    std::cout << "display\n";
	glutSwapBuffers();
}
void mod(float & a, float & da)
{
	a += da;
	if (a < 0)
	{
		a = 0; da = -da;
	}
	else if (a > 400)
	{
		a = 400; da = -da;
	}
}

// This function will be executed when the event queue is empty.
void idle()
{
    mod(x0, dx0);
    mod(y0, dy0);
    mod(x1, dx1);
    mod(y1, dy1);
    std::cout << "idel\n";
    glutPostRedisplay();
}
int main(int argc, char ** argv)
{
    mygllib::init2d_double();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}