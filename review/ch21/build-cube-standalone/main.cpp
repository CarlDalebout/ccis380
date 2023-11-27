#include <cmath>
#include <iostream>
#include <GL/freeglut.h>
#include "gl3d.h"
#include "View.h"
#include "SingletonView.h"
#include "Keyboard.h"
#include "Reshape.h"
#include "Material.h"
#include "Light.h"

mygllib::Light light;
GLfloat light_model_ambient[] = {1.0, 1.0, 1.0, 1.0};
int y_axis_angle = 0;

void init()
{
    mygllib::View & view = *(mygllib::SingletonView::getInstance());
    view.eyex() = 3.0f;
    view.eyey() = 1.5f;
    view.eyez() = 4.0f;
    view.zNear() = 0.1f;
    view.lookat();    

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    mygllib::Light::all_on();
    light.on();
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
}


void draw_red_plastic_sphere(float radius)
{
    mygllib::Material mat(mygllib::Material::RED_PLASTIC);
    mat.set();
    glutSolidSphere(radius, 20, 20);
}


void draw_cube()
{
    /*
                y
                
                |
                |
                |
                |
             p4 +--------+ p5
               /|       /|
              / |      / |
           p0+--------+p1|
             |  |     |  |
             |p7+-----|--+ p6 ------------- x
             | /      | /
             |/       |/
             +--------+
            p3        p2
           /
          /
         /
         
       z
       
    */
    static float p0[] = {0, 1, 1};
    static float p1[] = {1, 1, 1};
    static float p2[] = {1, 0, 1};
    static float p3[] = {0, 0, 1};
    static float p4[] = {0, 1, 0};
    static float p5[] = {1, 1, 0};
    static float p6[] = {1, 0, 0};
    static float p7[] = {0, 0, 0};

    // Declare p4, p5, p6, p7
    
    {
        // 2nd run:
        // Experiment: Change GL_CCW to GL_CW (and then change back)
        // CCW = counter clockwise
        // CW = clockwise
        glFrontFace(GL_CCW); 
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        glBegin(GL_QUADS);
        {
            // front side of cube
            // 5th run:
            // Experiment: try different normal vector
            glNormal3f(0, 0, 1); 
            glVertex3fv(p3); 
            glVertex3fv(p2); 
            glVertex3fv(p1); 
            glVertex3fv(p0);
            
            // right side of cube
            glNormal3f(1, 0, 0); 
            glVertex3fv(p2); 
            glVertex3fv(p6); 
            glVertex3fv(p5); 
            glVertex3fv(p1);
            
            // back side of cube
            glNormal3f(0, 0, -1); 
            glVertex3fv(p6); 
            glVertex3fv(p7); 
            glVertex3fv(p4); 
            glVertex3fv(p5);

            // left side of cube
            glNormal3f(-1, 0, 0); 
            glVertex3fv(p7); 
            glVertex3fv(p3); 
            glVertex3fv(p0); 
            glVertex3fv(p4);

            // 7th run: top of cube 
            glNormal3f(0, 1, 0); 
            glVertex3fv(p0); 
            glVertex3fv(p1); 
            glVertex3fv(p5); 
            glVertex3fv(p4);

            // 8th run: bottom of cube
            glNormal3f(0, -1, 0);
            glVertex3fv(p7); 
            glVertex3fv(p6); 
            glVertex3fv(p2); 
            glVertex3fv(p3);

        }
        glEnd();
        
        // Sphere in the box
        glPushMatrix();
        {
            glTranslatef(0.5, 0.5, 0.5);
            draw_red_plastic_sphere(0.2);
        }
        glPopMatrix();
        
        // This quad has red plastic material because of the red plastic ball
        // has set the material to red plastic.
        glTranslatef(1.5, 0, 0);
        glBegin(GL_QUADS);
        {
            glNormal3f(0, 0, 1);
            glVertex3fv(p0); glVertex3fv(p1); glVertex3fv(p2); glVertex3fv(p3);
        }
        glEnd();
    }   
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    {
        glRotatef(y_axis_angle, 0, 1, 0);
        mygllib::Light::all_off();
        mygllib::draw_axes();
        mygllib::draw_xz_plane();
        mygllib::Light::all_on();

        mygllib::Material mat(mygllib::Material::CYAN_PLASTIC);
        mat.set();
        draw_cube();
        glPushMatrix();
        {
            glTranslatef(light.x(), light.y(), light.z());
            draw_cube();
        }

    }
    glPopMatrix();
    glutSwapBuffers();
}


void keyboard(unsigned char key, int x, int y)
{
    mygllib::View & view = *(mygllib::SingletonView::getInstance());
    bool reset = false;
    switch (key)
    {
        case 'x': view.eyex() -= 0.1; reset = true; break;
        case 'X': view.eyex() += 0.1; reset = true; break;
        case 'y': view.eyey() += 0.1; reset = true; break;
        case 'Y': view.eyey() -= 0.1; reset = true; break;
        case 'z': view.eyez() += 0.1; reset = true; break;
        case 'Z': view.eyez() -= 0.1; reset = true; break;
            
        case 'r': y_axis_angle += 1; reset = true; break;
        case 'R': y_axis_angle -= 1; reset = true; break;
        
        case '1': light.x() += 0.1; reset = true; break;
        case '2': light.x() -= 0.1; reset = true; break;
        case '3': light.y() += 0.1; reset = true; break;
        case '4': light.y() -= 0.1; reset = true; break;
        case '5': light.z() += 0.1; reset = true; break;
        case '6': light.z() -= 0.1; reset = true; break;
    }
    if (reset)
    {
        glLoadIdentity();
        view.lookat();
        light.set();
        glutPostRedisplay();
    }
}


int main(int argc, char ** argv)
{
    std::cout << "eye control: x,X,y,Y,z,Z,R\n"; 
    std::cout << "light control: 1,2,3,4,5,6\n";
    std::cout << "see keyboard function for details\n";
    
    mygllib::init3d();
    init();

    glutDisplayFunc(display);
    glutReshapeFunc(mygllib::Reshape::reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    
    return 0;
}
