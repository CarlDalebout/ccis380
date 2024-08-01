#include <iostream>
#include <cmath>
#include <vector>
#include <GL/freeglut.h>
#include "../../../a/mygllib/gl2d.h"

// mouse cursor/pointer position when user presses
int x = 200, y = 200; 

// mouse button
bool mouse_down = false;

void regular_polygon(float x, float y, float r, int num_points)
{
    glBegin(GL_LINE_LOOP);
    // glColor3f(color_r, color_g, color_b);
    for(float i = 0; i < 360; i += 360/num_points)
    {
        float rad = i * 0.01745;
        glVertex2f(r*cos(rad)+x, r*sin(rad)+y);
    }
    glEnd();
}

void circle(float x, float y, float r, int num_points=-1)
{
    
    if(num_points == -1)
        regular_polygon(x, y, r, 30);
    else 
        regular_polygon(x, y, r, num_points);
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  if (mouse_down)
  {
    glColor3f(1.0f, 0.0f, 0.0f); // red
  }
  else
  {
    glColor3f(0.0f, 0.0f, 1.0f); // blue
  }
  glBegin(GL_LINES);
  glVertex2i(0, 0);
  glVertex2i(x, y);
  glEnd();
  glutSwapBuffers();
}
void mouse(int button, int state, int x, int y)
{
  // Set global x to the local x and global y to local y.
  ::x = x;
  ::y = 400 - y;
  mouse_down = (state == GLUT_DOWN);
  switch (button)
  {
    case GLUT_LEFT_BUTTON: 
    {
      std::cout << "left " << (::mouse_down? "down" : "up") << std::endl; 
    } break;
    
    case GLUT_MIDDLE_BUTTON: 
    {
      std::cout << "middle" << (::mouse_down? "down" : "up") << std::endl;
    } break;
    
    case GLUT_RIGHT_BUTTON: 
    {
      std::cout << "right" << (::mouse_down? "down" : "up") << std::endl; 
    } break;
  }

  glutPostRedisplay();
}
int main(int argc, char ** argv)
{
  mygllib::init2d();
  glLineWidth(50);
  glutDisplayFunc(display);
  glutMouseFunc(mouse);
  glutMainLoop();
  return 0;
}