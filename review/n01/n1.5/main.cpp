#include <iostream>
#include <string>
#include <GL/freeglut.h>
int main(int argc, char ** argv)
{
    // The following is the least number of statements that GLUT must
    // execute in order for glGetString(GL_VERSION) to work.
    glutInit(&argc, argv);
    glutCreateWindow("OpenGL!!!");

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << '\n';
    std::cout << "GLSL version: "
              << glGetString(GL_SHADING_LANGUAGE_VERSION) << '\n';
    
    // Alternative 1
    const GLubyte * s;
    s = glGetString(GL_VERSION);
    std::cout << "OpenGL version: " << s << '\n';
    
    // Alternative 2
    std::string t = (char *)s;
    std::cout << "OpenGL version: " << t << '\n';
    
    return 0;
}
