#include <iostream>
#include <cmath>
#include <GL/freeglut.h>
#include "gl3d.h"
#include "View.h"
#include "SingletonView.h"
#include "Reshape.h"

GLboolean light_on;
GLfloat light_ambient[4];
GLfloat light_diffuse[4];
GLfloat light_specular[4];
GLfloat light_position[4];

void init()
{
    glEnable(GL_DEPTH_TEST);

    mygllib::View & view = *(mygllib::SingletonView::getInstance()); 
    view.eyex() = 2.0f;
    view.eyey() = 2.0f;
    view.eyez() = 5.0f;
    view.set_projection();
    view.lookat();
    
    glViewport(0, 0, 400, 400);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

    // Turn on lighting
    light_on = true;
    glEnable(GL_LIGHTING);

    // Setting Light0
    light_ambient[0] = 0.0;
    light_ambient[1] = 0.0;
    light_ambient[2] = 1.0;
    light_ambient[3] = 0.0;
    
    light_diffuse[0] = 1;
    light_diffuse[1] = 1;
    light_diffuse[2] = 1;
    light_diffuse[3] = 1;
    
    light_specular[0] = 1;
    light_specular[1] = 1;
    light_specular[2] = 1;
    light_specular[3] = 1;

    light_position[0] = 0;
    light_position[1] = 0;
    light_position[2] = 1;
    light_position[3] = 0;

    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        
    glShadeModel(GL_SMOOTH); // Run with GL_FLAT
    glEnable(GL_NORMALIZE);
}


void draw_teapot()
{
    GLfloat mat_ambient[] = {0.24725, 0.1995, 0.0745, 1.0};
    GLfloat mat_diffuse[] = {0.75164, 0.60648, 0.22648, 1.0};
    GLfloat mat_specular[] = {0.628281, 0.555802, 0.366065, 1.0};
    GLfloat mat_shininess[] = {128.0 * 0.9};
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);    
    glutSolidTeapot(1.0);
}


void triangle()
{
    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0); glVertex3f(0, 0, 0);
    glColor3f(0, 1, 0); glVertex3f(1, 0, 0);
    glColor3f(0, 0, 1); glVertex3f(0.5, 1, 0);
    glEnd();
}


void display()
{    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDisable(GL_LIGHTING);
    mygllib::draw_xz_plane();
    mygllib::draw_axes();

    for (int z = 0; z >= -10; --z)
    {
        glPushMatrix();
        glTranslatef(0, 0, z);
        triangle();
        glPopMatrix();
    }

    if (light_on) glEnable(GL_LIGHTING);
    glColor3f(1, 0, 0);
    draw_teapot();
    glutSwapBuffers();
}


void keyboard(unsigned char key, int x, int y)
{
    mygllib::View & view = *(mygllib::SingletonView::getInstance()); 

    switch(key)
    {
        case 'x': view.eyex() -= 0.1; break;
        case 'X': view.eyex() += 0.1; break;
        case 'y': view.eyey() -= 0.1; break;
        case 'Y': view.eyey() += 0.1; break;
        case 'z': view.eyez() -= 0.1; break;
        case 'Z': view.eyez() += 0.1; break;
            
        case 'v': view.fovy() -= 0.1; break;
        case 'V': view.fovy() += 0.1; break;            
        case 'a': view.aspect() -= 0.1; break;
        case 'A': view.aspect() += 0.1; break;
        case 'n': view.zNear() -= 0.1; break;
        case 'N': view.zNear() += 0.1; break;
        case 'f': view.zFar() -= 0.1; break;
        case 'F': view.zFar() += 0.1; break;

        // light position
        case '!':
            light_positipon[0] = -1;
            light_position[1] = 0; 
            light_position[2] = 0;
            break;
        case '@':
            light_position[0] = +1;
            light_position[1] = 0; 
            light_position[2] = 0;
            break;
        case '#':
            light_position[0] = 0;
            light_position[1] = -1; 
            light_position[2] = 0;
            break;
        case '$':
            light_position[0] = 0;
            light_position[1] = +1; 
            light_position[2] = 0;
            break;
        case '%':
            light_position[0] = 0;
            light_position[1] = 0; 
            light_position[2] = -1;
            break;            
        case '^':
            light_position[0] = 0;
            light_position[1] = 0; 
            light_position[2] = +1;
            break;
        // Turning light on and off 
        case '&':
            light_on = true;
            break;
        case '*':
            light_on = false;
            break;
    }
    view.set_projection();
    view.lookat();
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glutPostRedisplay();
}


int main(int argc, char ** argv)
{
    mygllib::init3d();
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(mygllib::Reshape::reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
  
    return 0;
}
