#include <GL/freeglut.h>
void display()
{}
int main(int argc, char ** argv)
{
glutInit(&argc, argv);
glutInitWindowPosition(100, 100);
glutInitWindowSize(200, 200);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
glutCreateWindow("OpenGL!!!");
glutDisplayFunc(display);
glutMainLoop();
return 0;
}