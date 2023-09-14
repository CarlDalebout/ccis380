#include <GL/freeglut.h>
#include "../mygllib/gl2d.h"
#include <vector>

const int SIZE = 1024;
int level = 0;

struct point
{
    float x = 0;
    float y = 0;
};

std::vector<point>points(SIZE);

void addPoints()
{
    
}

void drawtriangle(float x, float y, float scale, int level)
{
    if(level == 0)
    //bottomLeft Triangle
    glColor3f(0.0f, 0.0f, 1.0f); // blue
    glVertex2f( x * scale, y * scale);
    
    glColor3f(0.0f, 0.0f, 1.0f); // blue
    glVertex2f((x + 100) * scale, (y + 200) * scale);

    glColor3f(0.0f, 0.0f, 1.0f); // blue
    glVertex2f((x + 200) * scale, y * scale);

    //Top Triangle
    glColor3f(0.0f, 0.0f, 1.0f); // blue
    glVertex2f((x + 100) * scale, (y + 200) * scale);
    
    glColor3f(0.0f, 0.0f, 1.0f); // blue
    glVertex2f((x + 200) * scale, (y + 400) * scale);
    
    glColor3f(0.0f, 0.0f, 1.0f); // blue
    glVertex2f((x + 300) * scale, (y + 200) * scale);
    
    //bottomRight Blue Triangle
    glColor3f(0.0f, 0.0f, 1.0f); // blue
    glVertex2f( (x + 200) * scale, y * scale);
    
    glColor3f(0.0f, 0.0f, 1.0f); // blue
    glVertex2f((x + 300) * scale, (y + 200) * scale);

    glColor3f(0.0f, 0.0f, 1.0f); // blue
    glVertex2f((x + 400) * scale, y * scale);
    
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);

    drawtriangle(200, 400, 0.5);
    drawtriangle(0, 0, 0.5);
    drawtriangle(400, 0, 0.5);

    glEnd();
    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case ' ':
        level++;
        break;
    
    default:
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char ** argv)
{
    mygllib::init2d();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
