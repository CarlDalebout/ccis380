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

class Body
{
public:
    double mass;
    vec4f p;
    vec4f v;
    float radius;
}

void init()
{
    mygllib::View & view = *(mygllib::SingletonView::getInstance());
    view.eyex() = 3.0f;
    view.eyey() = 1.5f;
    view.eyez() = 4.0f;
    view.zNear() = 0.1f;
    view.lookat();    

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    mygllib::Light::all_on();
    light.on();
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
}

void draw_sphere(float radius)
{
    glutSolidSphere(radius, 20, 20);
}

void draw_triangle_strip()
{
    /*
       p0      p2       p
        +------+------+------+
        |     /|     /|     /|
        |    / |    / |    / |
        |   /  |   /  |   /  |
        |  /   |  /   |  /   |
        | /    | /    | /    |
        |/     |/     |/     |
        +------+------+------+
       p1      p3           p4
    */


    // p0, p1, p2, p3, p4, p5, p6, p7
    // t0 = p0, p1, p2
    // t1 = p2, p1, p3
    // t0 = p3, p4, p5
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
    
    {
        // 2nd run:
        // Experiment: Change GL_CCW to GL_CW (and then change back)
        // CCW = counter clockwise
        // CW = clockwise
        glFrontFace(GL_CCW); 

        // 3rd run:
        // Experiment:
        // - Cull back face using GL_BACK
        // glEnable(GL_CULL_FACE);
        // glCullFace(GL_BACK);
       
        // 4th run:
        // Experiment - Cull front face using GL_FRONT

         glBegin(GL_QUADS);
        {
            // front side of cube
            // 5th run:
            // Experiment: try different normal vector
            glNormal3f(0, 0, 1); 
            glVertex3fv(p3); glVertex3fv(p2); glVertex3fv(p1); glVertex3fv(p0);
            
            // right side of cube
            
            // back side of cube

            // left side of cube
            
            // 7th run: top of cube 
            
            // 8th run: bottom of cube
        }
        glEnd();
        
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

        mygllib::Material mat(mygllib::Material::YELLOW_PLASTIC);
        mat.set();
        draw_sphere(1.0f);
        glPushMatrix();
        {
            glTranslatef(1.5f, 0.0f, 0.0f);
            mygllib::Material mat(mygllib::Material::WHITE_PLASTIC);
            mat.set();
            draw_sphere(0.1f);
        }
        glPopMatrix();
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
