#include <GL/freeglut.h>
#include "../../../a/mygllib/gl2d.h"

// Coordinates and color of one endpoint of the line
const int X0 = 100;
const int Y0 = 100;
const float R0 = 1.0f;
const float G0 = 0.0f;
const float B0 = 0.0f;

int x0 = X0, y0 = Y0;
float r0 = R0, g0 = G0, b0 = B0;

// Coordinates and color of the other endpoint of the line
const int X1 = 200;
const int Y1 = 200;
const float R1 = 0.0f;
const float G1 = 0.0f;
const float B1 = 1.0f;

int x1 = X1, y1 = Y1;
float r1 = R1, g1 = G1, b1 = B1;

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_LINES);
    glColor3f(r0, g0, b0);
    glVertex2i(x0, y0);
    glColor3f(r1, g1, b1);
    glVertex2i(x1, y1);
  glEnd();
  glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key)
  {
    //up endpoint 0
    case 'w':
    case 'W': y0++; break;
    //down endpoint 0
    case 's':
    case 'S': y0--; break;
    //left endpoint 0
    case 'a': 
    case 'A': x0--; break;
    //right endpoint 0
    case 'd': 
    case 'D': x0++; break;

    //endpoint 0 red
    case '1': if(r0 < 1) 
                r0+= 0.01; 
              break;
    case '!': if(r0 > 0) 
                r0-= 0.01; 
              break;
    //endpoint 0 green
    case '2': if(g0 < 1)
                g0+= 0.01; 
              break;
    case '@': if(g0 > 0)
                  g0-= 0.01; 
                break;
    //endpoint 0 blue
    case '3': if(b0 < 1)
                b0+= 0.01; 
              break;
    case '#': if(b0 > 0)
                b0-= 0.01; 
              break;

    //endpoint 1 red
    case '4': if(r1 < 1)
                r1+= 0.01; 
              break;
    case '$': if(r1 > 0)
                r1-= 0.01; 
              break;
    //endpoint 1 green
    case '5': if(g1 < 1)
                g1+= 0.01; 
              break;
    case '%': if(g1 > 0)
                g1-= 0.01; 
              break;
    //endpoint 1 blue
    case '6': if(b1 < 1)
                b1+= 0.01; 
              break;
    case '^': if(b1 > 0)
                b1-= 0.01; 
              break;
    
  }
  display();
}

void specialkeyboard(int key, int x, int y)
{
  switch (key)
  {
    //up endpoint 1
    case GLUT_KEY_UP: y1++; break;
    //down endpoint 1
    case GLUT_KEY_DOWN: y1--; break;
    //left endpoint 1
    case GLUT_KEY_LEFT: x1--; break;
    //right endpoint 1
    case GLUT_KEY_RIGHT: x1++; break;
    //reset
    case GLUT_KEY_F1: x0 = x0; y0 = Y0; 
                      r0 = R0; g0 = G0; b0 = B0;
                      x1 = X1; y1 = Y1;
                      r1 = R1; g1 = G1; b1 = B1;
  }
  display();
}

int main(int argc, char ** argv)
{
  mygllib::init2d();

  glLineWidth(10.0f);
  glEnable(GL_LINE_SMOOTH);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(specialkeyboard);

  glutMainLoop();
  
  return 0;
}
