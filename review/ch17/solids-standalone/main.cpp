#include <GL/freeglut.h>
#include "gl3d.h"
#include "View.h"
#include "SingletonView.h"
#include "Keyboard.h"
#include "Reshape.h"
#include "Material.h"
#include "Light.h"

mygllib::Light light;


void init()
{
    mygllib::View & view = *(mygllib::SingletonView::getInstance());
    view.eyex() = 10.0f;
    view.eyey() = 5.0f;
    view.eyez() = 10.0f;
    view.set_projection();
    view.lookat();

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);  

    mygllib::Light::all_on();    
    light.on();
    light.set();

    mygllib::Material mat(mygllib::Material::GOLD);
    mat.set();
}


void draw_solids()
{
    glPushMatrix();
    {
        glutSolidTeapot(1.0);
        glTranslatef(3, 0, 0);
        glutSolidTorus(0.2, 0.5, 20, 20);
        glTranslatef(3, 0, 0);
        glutSolidCone(0.5, 2, 20, 20); // radius, height
        glTranslatef(3, 0, 0);
        glutSolidTetrahedron();

        // Disk
        glTranslatef(2,0,0);
        {
            GLUquadric * p = gluNewQuadric();
            gluQuadricDrawStyle(p, GLU_FILL);
            gluDisk(p, 0.5, 1, 20, 20);
            gluDeleteQuadric(p);
        }
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(0,0,3);
        glutSolidCube(1.0);
        glTranslatef(0,0,3);
        glutSolidSphere(1.0, 20, 20);

        // Cylinder
        glTranslatef(0,0,3);
        GLUquadric * p = gluNewQuadric();
        gluQuadricDrawStyle(p, GLU_FILL);
        gluCylinder(p, 0.5, 0.75, 1, 20, 20);
        gluDeleteQuadric(p);
        
    }
    glPopMatrix();
}


void display()
{    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    mygllib::Light::all_off();
    mygllib::draw_axes();
    mygllib::draw_xz_plane();
    mygllib::Light::all_on();
    draw_solids();
    glutSwapBuffers();
}


int main(int argc, char ** argv)
{
    mygllib::WIN_W = 600;
    mygllib::WIN_H = 600;
    mygllib::init3d();
    init();    
    glutDisplayFunc(display);
    glutReshapeFunc(mygllib::Reshape::reshape);
    glutKeyboardFunc(mygllib::Keyboard::keyboard);    
    glutMainLoop();
  
    return 0;
}
