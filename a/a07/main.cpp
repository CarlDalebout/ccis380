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
    view.eyey() = 5.0f;
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

float yoffset = 5;
float xoffset = 0;
float zoffset = 0;

float base_x_axis = 0;
float base_y_axis = 0;
float base_z_axis = 0;
float elbow_x_axis = 0;
float elbow_y_axis = 0;
float elbow_z_axis = 0;

void triangle()
{
    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0); glVertex3f(0, 0, 0);
    glColor3f(0, 1, 0); glVertex3f(1, 0, 0);
    glColor3f(0, 0, 1); glVertex3f(0.5, 1, 0);
    glEnd();
}

void cylinder(float radius, double length, int slice_per_ring = 20, int rings = 20)
{
    GLfloat mat_ambient[] = {0.24725, 0.1995, 0.0745, 1.0};
    GLfloat mat_diffuse[] = {0.4, 0.4, 0.4, 1.0};
    GLfloat mat_specular[] = {0.628281, 0.555802, 0.366065, 1.0};
    GLfloat mat_shininess[] = {128.0 * 0.9};
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glutSolidCylinder(radius, length, slice_per_ring, rings);
}

void draw_base()
{
    GLfloat mat_ambient[] = {0.24725, 0.1995, 0.0745, 1.0};
    GLfloat mat_diffuse[] = {0.4, 0.4, 0.4, 1.0};
    GLfloat mat_specular[] = {0.628281, 0.555802, 0.366065, 1.0};
    GLfloat mat_shininess[] = {128.0 * 0.9};
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glPushMatrix();
        glScalef(6.0f, 1.0f, 6.0f);
        glTranslatef(0.0f, 0.5f, 0.0f);
        glutSolidCube(1.0f);
    glPopMatrix();
}

void draw_shoulder_joint()
{
    GLfloat mat_ambient[] = {0.24725, 0.1995, 0.0745, 1.0};
    GLfloat mat_diffuse[] = {0.8, 0.8, 0.0f, 1.0};
    GLfloat mat_specular[] = {0.628281, 0.555802, 0.366065, 1.0};
    GLfloat mat_shininess[] = {128.0 * 0.9};
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);    
    glPushMatrix();
    glTranslatef(0.0f, 1.0f, 0.0f);
    glutSolidSphere(1.2f, 20, 20);
    glPopMatrix();
    
}

void display()
{    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDisable(GL_LIGHTING);
    mygllib::draw_xz_plane();
    mygllib::draw_axes();

    if (light_on) glEnable(GL_LIGHTING);
    glColor3f(1, 0, 0);
    draw_base();
    glPushMatrix();
    {
        glRotatef(base_x_axis, 1.0f, 0.0f, 0.0f);
        glRotatef(base_y_axis, 0.0f, 1.0f, 0.0f);
        glRotatef(base_z_axis, 0.0f, 0.0f, 1.0f);
        draw_shoulder_joint();
        glPushMatrix();
            glTranslatef(0.0f, 1.5f, 0.0f);
            glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
            cylinder(0.6f, 4.0f);
        glPopMatrix();
        glPushMatrix();
        {
            glTranslatef(0.0f, 5.5f, 0.0f);
            draw_shoulder_joint();
            // glTranslatef(0.0f, 2.0f, 0.0f);
            glPushMatrix();
                glRotatef(270.0f + elbow_x_axis, 1.0f, 0.0f, 0.0f);
                glRotatef(elbow_y_axis, 0.0f, 1.0f, 0.0f);
                glRotatef(elbow_z_axis, 0.0f, 0.0f, 1.0f);
                cylinder(0.6f, 4.0f);
            glPopMatrix();
        }
        glPopMatrix();
    }
    glPopMatrix();
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

        //moveing objects
        case '+': yoffset += 0.1; std::cout << yoffset << std::endl; break;
        case '-': yoffset -= 0.1; std::cout << yoffset << std::endl; break;
        case '*': xoffset += 0.1; std::cout << xoffset << std::endl; break;
        case '/': xoffset -= 0.1; std::cout << xoffset << std::endl; break;
        case '=': zoffset += 0.1; std::cout << zoffset << std::endl; break;
        case '_': zoffset -= 0.1; std::cout << zoffset << std::endl; break;

        case '1': base_x_axis += 5; std::cout << base_x_axis << std::endl; break;
        case '2': base_x_axis -= 5; std::cout << base_x_axis << std::endl; break;
        case '3': base_y_axis += 5; std::cout << base_y_axis << std::endl; break;
        case '4': base_y_axis -= 5; std::cout << base_y_axis << std::endl; break;
        case '5': base_z_axis += 5; std::cout << base_z_axis << std::endl; break;
        case '6': base_z_axis -= 5; std::cout << base_z_axis << std::endl; break;
        
        case 'q': elbow_x_axis += 5; std::cout << elbow_x_axis << std::endl; break;
        case 'Q': elbow_x_axis -= 5; std::cout << elbow_x_axis << std::endl; break;
        case 'w': elbow_y_axis += 5; std::cout << elbow_y_axis << std::endl; break;
        case 'W': elbow_y_axis -= 5; std::cout << elbow_y_axis << std::endl; break;
        case 'e': elbow_z_axis += 5; std::cout << elbow_z_axis << std::endl; break;
        case 'E': elbow_z_axis -= 5; std::cout << elbow_z_axis << std::endl; break;
        
        // light position
        case '!':
            light_position[0] = -1;
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
            light_position[0] = -1;
            light_position[1] = +1; 
            light_position[2] = +1;
            break;
        // Turning light on and off 
        case 'l':
            light_on = true;
            break;
        case 'L':
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
