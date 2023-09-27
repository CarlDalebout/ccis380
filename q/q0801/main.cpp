#include <iostream>
#include <cmath>
#include <GL/freeglut.h>
#include "../../a/mygllib/gl2d.h"

const float PI = 3.14159246;
float t = 0.0f;
float dt = PI / 180.0f / 2.0f;

void print_arrow()
{
    glColor3f(1, 0, 0);
    glBegin(GL_TRIANGLES);
    glVertex2f(100 * cos(t) + 200, 100 * sin(t) + 200);
    glVertex2f(20 * cos(t + ))
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    print_arrow();

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
        case '+':
            t += dt; 
            std::cout << "angle: " << int(t * 180 / PI) << std::endl;
            break;

        case '-':
            t -= dt; 
            std::cout << "angle: " << int(t * 180 / PI) << std::endl;
            break;
    }
    glutPostRedisplay();

}

int main()
{
    mygllib::init2d(400, 400);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}