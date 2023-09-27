#include <ctime>
#include <cstdlib>
#include <tgmath.h>
#include <vector>
#include <iostream>
#include <GL/freeglut.h>
#include "../mygllib/gl2d.h"
#include "complex.h"
// #include <complex.h>

double   dr = 0.005;
int     MAX_ITER = 100;

int Mandle(complex c,
           complex t = {0,0},
           int counter = 0)
{
    
    // To eliminate out of bound values.
    if (abs(t) > 2) {
        glColor3f(0.5 * (abs((t * t)) / abs((t - c) * c)), 0, 1.0 * (abs((t * t)) / abs((t - c) * c)));        
        glVertex2f(c.re(), c.im() );
        return 0;
    }
 
    // To put about the end of the fractal,
    // the higher the value of the counter,
    // The more accurate the fractal is generated,
    // however, higher values cause
    // more processing time.
    if (counter == 100) {
        glColor3f(1.0 - 1.0 * abs(t) / abs(c), 
                  1.0 - 1.0 * abs(t) / abs(c), 
                  1.0 - 1.0 * abs(t) / abs(c));
        glVertex2f(c.re(), c.im());
        return 0;
    }
 
    // recursively calling Mandle with increased counter
    // and passing the value of the squares of t into it.
    Mandle(c, (t*t + c), counter + 1);
 
    return 0;
}
 

int MandleSet()
{
 
    // Calling Mandle function for every
    // point on the screen.
        for (double x = -3; x < 3; x += dr) {
        for (double y = -2; y < 2; y += dr) {
            complex temp = {x, y};
            Mandle(temp);
            
        }
    }
    return 0;
}

void display()
{
    // glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw points
    glBegin(GL_POINTS);

    std::cout << "running display" <<std::endl;
    MandleSet();

    std::cout << "ran display\n";
    glEnd();
    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case ' ':
        break;
    
    default:
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char ** argv)
{   
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(900, 400);
    glutInitDisplayMode((GLUT_SINGLE | GLUT_RGBA));
    glutCreateWindow("OpenGL!!!");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-3, 3, -2, 2);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    // complex temp(-1.4, -0.0999997);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}