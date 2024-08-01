#include <GL/freeglut.h>
#include "../../mygllib/gl2d.h"
#include <vector>

int level = 0;

struct point
{
    float x = 0;
    float y = 0;
};

std::vector<point>points{{0, 0}, {200, 400}, {400, 0}};

void addPoints()
{
    unsigned int i = 0;
    while(i < points.size())
    {
        point ab = {(points[i].x + points[i+1].x)/2, (points[i].y + points[i+1].y)/2}; 
        point ac = {(points[i].x + points[i+2].x)/2, (points[i].y + points[i+2].y)/2};
        point bc = {(points[i+1].x + points[i+2].x)/2, (points[i+1].y + points[i+2].y)/2};
        points.insert(points.begin() + i + 1, ab); //i is still pointing at a
        points.insert(points.begin() + i + 2, ac); 
        i += 3;// i is pointing to b
        points.insert(points.begin() + i + 1, ab); //i is still pointing at b
        points.insert(points.begin() + i + 2, bc);
        i += 3;
        points.insert(points.begin() + i + 1, ac); //i is still pointing at c
        points.insert(points.begin() + i + 2, bc);
        i += 3;        
    }
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
    if(level < 7)
    {
        level++;
        addPoints();
    }
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
        if(level < 7)
        {
            level++;
            addPoints();
        }
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
