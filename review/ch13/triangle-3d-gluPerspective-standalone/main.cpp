#include <iostream>
#include <GL/freeglut.h>
#include "gl3d.h"

float eyex;
float eyey;
float eyez;
float refx;
float refy;
float refz;

float fovy = 45.0;  // angle along y-axis wrt camera eye
float aspect = 1.0; // x/y of cross-sectional area of frustum
                    // for square, use 1.0
float zNear = 1.0;
float zFar = 10.0;

    
void init()
{
    eyex = 5.0f;
    eyey = 1.0f;
    eyez = 5.0f;
    refx = 0.0f;
    refy = 0.0f;
    refz = 0.0f;

    fovy = 90.0;
    aspect = 1.0;
    zNear = 1;
    zFar = 100.0;

    // Set projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fovy, aspect,
                   zNear, zFar);    
    
    // Set model view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyex, eyey, eyez, 
              refx, refy, refz, 
              0.0, 1.0, 0.0);       
    
    glViewport(0, 0, 400, 400);

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
}


void triangle()
{
    glBegin(GL_TRIANGLES);
    {
        glColor3f(1,0,0); glVertex3f(0,0,0);
        glColor3f(0,1,0); glVertex3f(1,0,0);
        glColor3f(0,0,1); glVertex3f(0.5,1,0);
    }
    glEnd();
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT); // NOTE: Make sure depth data is cleared
    
    mygllib::draw_xz_plane();
    mygllib::draw_axes();

    for (int z = 0; z >= -10; z -= 1)
    {
        glPushMatrix();
        glTranslatef(0, 0, z);
        triangle();
        glPopMatrix();
    }
    
    glutSwapBuffers();
}


void reshape(int w, int h)
{
    glViewport(0, 0, 400, 400);
}


void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 'x': eyex -= 0.1; break;
        case 'X': eyex += 0.1; break;
        case 'y': eyey -= 0.1; break;
        case 'Y': eyey += 0.1; break;
        case 'z': eyez -= 0.1; break;
        case 'Z': eyez += 0.1; break;
            
        case 'v': fovy -= 0.1; break;
        case 'V': fovy += 0.1; break;            
        case 'a': aspect -= 0.1; break;
        case 'A': aspect += 0.1; break;
        case 'n': zNear -= 0.1; break;
        case 'N': zNear += 0.1; break;
        case 'f': zFar -= 0.1; break;
        case 'F': zFar += 0.1; break;
    }

    // Set projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fovy, aspect, 
                   zNear, zFar);    

    // Set model view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyex, eyey, eyez,
              refx, refy, refz,
              0.0, 1.0, 0.0);

    glutPostRedisplay();
}

int main(int argc, char ** argv)
{
    glutInit(&argc, argv);    
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutCreateWindow("OpenGL!!!");

    glEnable(GL_DEPTH_TEST); // NOTE: make sure depth testing is on.
  
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
  
    return 0;
}
