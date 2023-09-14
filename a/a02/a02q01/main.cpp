#include <GL/freeglut.h>
#include "../mygllib/gl2d.h"
#include <vector>

int level = 0;

struct point
{
    float x = 0;
    float y = 0;
};

std::vector<point>points{{0, 0}, {100, 200}, {200, 0}, 
                         {100, 200}, {200, 400}, {300, 200},
                         {200, 0}, {300, 200}, {400, 0}};

void addPoints()
{
    //ahhhhhhhhhhhhhhhhh
}

void drawtriangle()
{
    for(unsigned int i = 0; i < points.size(); ++i)
    {
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(points[i].x, points[i].y);
    }    
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    addPoints();
    drawtriangle();
    // drawtriangle(0, 0, 0.5, 1);
    // drawtriangle(400, 0, 0.5, 1);

    glEnd();
    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case ' ':
        addPoints();
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
