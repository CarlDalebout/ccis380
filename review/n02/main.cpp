#include <iostream>
#include <GL/freeglut.h>
void display()
{
    static int count = 0;
    
    // Clear the screen
    count++;
    std::cout << "display() function executing ..." << count << std::endl;
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("OpenGL!!!");
    
    //-------------------------------------------------------------------------
    // Sets the clear screen color to white and register display() as the
    // display function.
    //-------------------------------------------------------------------------
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}
