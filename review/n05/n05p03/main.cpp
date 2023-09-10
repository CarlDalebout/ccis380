#include <cstdio>
#include <iostream>
#include <GL/freeglut.h>
#include <cmath>
const float PI = 3.14159246;
bool aa = false;
float t = 0.0f; // angle
float dt = PI / 180.0 / 2.0; // small change in angle
float linewidth = 1.0f;
float dlinewidth = 0.1f; // small change in line width
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    if (aa)
    {
        // Turn on line smoothing and select best
        glEnable(GL_LINE_SMOOTH);
        glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    }
    else
    {
        // Turn off line smoothing
        glDisable(GL_LINE_SMOOTH);
    }

    glBegin(GL_LINES);
    glVertex2f(0.0, 0.0);
    glVertex2f(400.0 * cos(t), 400.0 * sin(t));
    glEnd();
    
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 'y':
            aa = true;
            std::cout << "aa on" << std::endl;
            break;

        case 'n':
            std::cout << "aa off" << std::endl;
            aa = false;
            break;

        case '+':
            t += dt; if (t > PI/2.0) t = PI/2.0;
            std::cout << "angle: " << int(t * 180 / PI) << std::endl;
            break;

        case '-':
            t -= dt; if (t < 0) t = 0;
            std::cout << "angle: " << int(t * 180 / PI) << std::endl;
            break;

        case 'i':
            linewidth += dlinewidth;
            glLineWidth(linewidth);
            std::cout << "linewidth: " << linewidth << std::endl;
            break;

        case 'd':
            linewidth -= dlinewidth;
            if (linewidth < 1) linewidth = 1;
            glLineWidth(linewidth);
            std::cout << "linewidth: " << linewidth << std::endl;
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char ** argv)
{
    std::cout << "y: turn on aa (lines)\n"
              << "n: turn off aa (lines)\n"
              << "+: increase angle\n"
              << "-: decrease angle\n"
              << "i: increase line width\n"
              << "d: decrease line width\n";

    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("OpenGL!!!");

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0f, 400.0f, 0.0f, 400.0f);
    glColor3f(0.0f, 0.0f, 1.0f);

    // Turn on blending and set blending parameters
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glLineWidth(linewidth);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
