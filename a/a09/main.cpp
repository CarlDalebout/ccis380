#include <cmath>
#include <iostream>
#include <list>
#include <GL/freeglut.h>
#include <time.h>
#include "gl3d.h"
#include "View.h"
#include "SingletonView.h"
#include "Keyboard.h"
#include "Reshape.h"
#include "Material.h"
#include "Light.h"
#include "Heightmap.h"


mygllib::Light light;
GLfloat light_model_ambient[] = {0.0, 0.0, 0.0, 1.0};
int y_axis_angle = 0;

bool print_lines = true;
int n = 2;
Heightmap heightmap(n);
double roughness = 1;

void init()
{
    mygllib::View & view = *(mygllib::SingletonView::getInstance());
    view.eyex()     = -5.0f;
    view.eyey()     = 20.0f;
    view.eyez()     = 5.0f;
    view.zNear()    = 0.1f;
    view.zFar()     = 300.0f;

    view.aspect()   = 1;
    view.lookat();      

    srand(time(NULL));
    heightmap.Diamond_Square(roughness);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    mygllib::Light::all_off();
    light.y() = 300.0f;
    light.on();
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
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
        mygllib::Light::all_on();
        glPushMatrix();
        {
            
            glTranslatef(-pow(2, n)/2, 0, -pow(2, n)/2);
            // std::cout << heightmap << std::endl;
            if(print_lines)
                heightmap.draw_triangle_mesh_wired();
            else
                heightmap.draw_triangle_mesh_solid();
        }
        glPopMatrix();
    }
    glPopMatrix();
    glutSwapBuffers();
}

// // Timer Function for glutTimerFunc()
// void animate(int someValue)-
// {
    
//     glutPostRedisplay();
//     glutTimerFunc(1, animate, 1);
// }

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
        
        case 'n':
        {
            float product = sqrt(pow(view.eyex(), 2) + pow(view.eyey(), 2) + pow(view.eyez(), 2));
            view.eyex() -= view.eyex()/(product); 
            view.eyey() -= view.eyey()/(product); 
            view.eyez() -= view.eyez()/(product); 
            reset = true;
        } break;
        case 'N':
        {
            float product = sqrt(pow(view.eyex(), 2) + pow(view.eyey(), 2) + pow(view.eyez(), 2));
            view.eyex() += view.eyex()/(product); 
            view.eyey() += view.eyey()/(product); 
            view.eyez() += view.eyez()/(product); 
            reset = true;
        } break;

        case '-': n -= 1; heightmap = heightmap.resize(n); heightmap.Diamond_Square(roughness); reset = true; break;
        case '+': n += 1; heightmap = heightmap.resize(n); heightmap.Diamond_Square(roughness); reset = true; break;

        case 's': roughness -= 0.1; heightmap.Diamond_Square(roughness); reset = true; break;
        case 'S': roughness += 0.1; heightmap.Diamond_Square(roughness); reset = true; break;

        case 'p': print_lines = false; reset = true; break;
        case 'P': print_lines = true;  reset = true; break;

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

    mygllib::init3d(700, 700);
    init();

    glutDisplayFunc(display);
    glutReshapeFunc(mygllib::Reshape::reshape);
    glutKeyboardFunc(keyboard);
    // glutTimerFunc(1, animate, 1);
    glutMainLoop();
    
    return 0;
}
