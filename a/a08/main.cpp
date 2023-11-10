#include <cmath>
#include <iostream>
#include <list>
#include <GL/freeglut.h>
#include "gl3d.h"
#include "View.h"
#include "SingletonView.h"
#include "Keyboard.h"
#include "Reshape.h"
#include "Material.h"
#include "Light.h"
#include "Vec4f.h"
#include "Body.h"

const double G = 6.67408E-11;  // Newton's universal gravitational constant
const char NAMES[10][32] = {"SUN",
                            "MERCURY", "VENUS", "EARTH", "MARS",
                            "JUPITER", "SATURN", "URANUS", "NEPTUNE", "PLUTO"};
const double MASS[] = {1.989E30,
                       0.330E24, 4.87E24, 5.97E24, 0.642E24,
                       1898E24, 568E24, 86.8E24, 102E24, 0.0146E24};
const double PERIHELION[] = {0,
                             46.0E9, 107.5E9, 147.1E9, 206.6E9,
                             740.5E9, 1352.6E9, 2741.3E9, 4444.5E9, 4436.8E9};
const double APHELION[] = {0,
                           69.8E9, 108.9E9, 152.1E9, 249.2E9,
                           816.6E9, 1514.5E9, 3003.6E9, 4545.7E9, 7375.9E9};
const float DIAMETER[] = {0,
                           4879E6, 12104E6, 12756E6, 6792E6,
                           142984E6, 120536E6, 51118E6, 49528E6, 2370E6};



mygllib::Light light;
GLfloat light_model_ambient[] = {0.0, 0.0, 0.0, 1.0};
int y_axis_angle = 0;

int pick_body = 1;

Body * body;
double dt = 300000;


void init()
{
    mygllib::View & view = *(mygllib::SingletonView::getInstance());
    view.eyex() = -150.0f;
    view.eyey() = 300.0f;
    view.eyez() = 100.0f;
    view.zNear() = 0.1f;
    view.zFar() = 3000.0f;
    view.aspect() = 1;
    view.lookat();    

    body = new Body[10];
    
    // SUN
    body[0].mass() = MASS[0];
    body[0].radius() = DIAMETER[0];

    for(int i = 1; i < 10; ++i)
    {
        body[i].mass() = MASS[i];
        vec4f position(PERIHELION[i], 0.0f, 0.0f);
        body[i].p() = position;
        vec4f velocity(0, 0, sqrt(G*MASS[0]*((2.0/PERIHELION[i])-(1/(0.5*(APHELION[i]+PERIHELION[i]))))));
        body[i].v() = velocity;
        body[i].radius() = DIAMETER[i]/2;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    mygllib::Light::all_on();
    light.y() = 300.0f;
    light.on();
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
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

    // static float p4[] = {0, 1, 0};
    // static float p5[] = {1, 1, 0};
    // static float p6[] = {1, 0, 0};
    // static float p7[] = {0, 0, 0};
    
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
        // mygllib::draw_xz_plane();
        mygllib::Light::all_on()
        ;
        glPushMatrix();
        {
            glScalef(1E-10, 1E-10, 1E-10);
            mygllib::Material mat(mygllib::Material::WHITE_PLASTIC);
            mat.set();
            for(int i = 1; i < 10; i++)
            {
                glPushMatrix();
                {   
                    // std::cout << "displaying " << NAMES[i] << " at position " << body[i].p().x() << " " << body[i].p().y() << " " << body[i].p().z() << std::endl;
                    glTranslatef(body[i].p().x(), body[i].p().y(), body[i].p().z());
                    glutSolidSphere(body[i].radius(), 25, 25);
                }
                glPopMatrix();
            }
        }
        glPopMatrix();
    }
    glPopMatrix();
    glutSwapBuffers();
}

// Timer Function for glutTimerFunc()
void animate(int someValue)
{
    vec4f F[10];
    for(int i = 1; i < 10; ++i)
    {
        F[i] = vec4f(0, 0, 0);
        if(body[i].p().x() != 0)
        F[i].x() += G*(MASS[0]*MASS[i])/pow(body[i].p().x(), 2); 
        if(body[i].p().y() != 0)
        F[i].y() += G*(MASS[0]*MASS[i])/pow(body[i].p().y(), 2); 
        if(body[i].p().z() != 0)
        F[i].z() += G*(MASS[0]*MASS[i])/pow(body[i].p().z(), 2); 
        
        for(int j = 0; j < 10; ++j)
        {
            if(j != i)
            {
                F[i].x() += G*(MASS[j]*MASS[i])/pow(body[i].p().x(), 2); 
                F[i].y() += G*(MASS[j]*MASS[i])/pow(body[i].p().y(), 2); 
                F[i].z() += G*(MASS[j]*MASS[i])/pow(body[i].p().z(), 2); 
            }
        }
    }

    for(int i = 1; i < 10; ++i)
    {
        // double ax = F[i].x() / MASS[i];
        // double ay = F[i].y() / MASS[i];
        // double az = F[i].z() / MASS[i];
        
        // body[i].v().x() = body[i].v().x() + ax * dt;
        // body[i].v().y() = body[i].v().y() + ay * dt;
        // body[i].v().z() = body[i].v().z() + az * dt;
        
        // body[i].p().x() = body[i].p().x() + body[i].v().x() * dt;
        // body[i].p().y() = body[i].p().y() + body[i].v().y() * dt;
        // body[i].p().z() = body[i].p().z() + body[i].v().z() * dt;
        
    }
    glutPostRedisplay();
    glutTimerFunc(1, animate, 1);
}

void keyboard(unsigned char key, int x, int y)
{
    mygllib::View & view = *(mygllib::SingletonView::getInstance());
    bool reset = false;
    switch (key)
    {
        case 'x': view.eyex() -= 5.0; reset = true; break;
        case 'X': view.eyex() += 5.0; reset = true; break;
        case 'y': view.eyey() += 5.0; reset = true; break;
        case 'Y': view.eyey() -= 5.0; reset = true; break;
        case 'z': view.eyez() += 5.0; reset = true; break;
        case 'Z': view.eyez() -= 5.0; reset = true; break;
            
        case 'r': y_axis_angle += 1; reset = true; break;
        case 'R': y_axis_angle -= 1; reset = true; break;
        
        case '1': light.x() += 0.1; reset = true; break;
        case '2': light.x() -= 0.1; reset = true; break;
        case '3': light.y() += 0.1; reset = true; break;
        case '4': light.y() -= 0.1; reset = true; break;
        case '5': light.z() += 0.1; reset = true; break;
        case '6': light.z() -= 0.1; reset = true; break;
        
        case '+': pick_body = (pick_body % 9) + 1; reset = true; break;
        case '-': pick_body = (pick_body % 9) - 1; reset = true; break;
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

    mygllib::init3d(700, 700);
    init();
    if(body[1].p().x() != 0)
    std::cout << G*(MASS[0]*MASS[1])/pow(body[1].p().x(), 2) << std::endl;
    if(body[1].p().y() != 0)
    std::cout << G*(MASS[0]*MASS[1])/pow(body[1].p().y(), 2) << std::endl;
    if(body[1].p().z() != 0)
    std::cout << G*(MASS[0]*MASS[1])/pow(body[1].p().z(), 2) << std::endl;



    glutDisplayFunc(display);
    glutReshapeFunc(mygllib::Reshape::reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(1, animate, 1);
    glutMainLoop();
    
    return 0;
}
