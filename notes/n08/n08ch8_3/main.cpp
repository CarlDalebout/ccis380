#include <iostream>
#include <GL/freeglut.h>
#include "../../../a/mygllib/gl2d.h"

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
}

//-----------------------------------------------------------------------------
// This function is executed when a key such as 'a', 'A', etc.
// is pressed.
//-----------------------------------------------------------------------------
void keyboard(unsigned char key, int x, int y)
{
  std::cout << "keyboard() ... "
  << key << ','
  << (unsigned int)(key) << ','
  << x << ','
  << y << std::endl;
}

//-----------------------------------------------------------------------------
// This function is executed when a special key (example: function key, arrow
// key, ...) is pressed.
//-----------------------------------------------------------------------------
void specialkeyboard(int key, int x, int y)
{
  std::cout << "specialkeyboard() ... "
  << key << ','
  << x << ','
  << y << std::endl;

  switch (key)
  {
    case GLUT_KEY_UP: std::cout << "up arrow" << std::endl; break;
    case GLUT_KEY_DOWN: std::cout << "down arrow" << std::endl; break;
    case GLUT_KEY_F1: std::cout << "F1" << std::endl; break;
  }
}

int main(int argc, char ** argv)
{
  mygllib::init2d();
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard); // callback for ASCII keys
  glutSpecialFunc(specialkeyboard); // callback for special keys
  glutMainLoop();
  return 0;
}
