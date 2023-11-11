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

int n = 3;
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

void draw_triangle_mesh(std::vector<std::vector<double>> heightmap, int x_offset = 0, int z_offset = 0)
{
    /*
       p0      p2     p4     p6
        +------+------+------+
        |     /|     /|     /|
        |    / |    / |    / |
        |   /  |   /  |   /  |
        |  /   |  /   |  /   |
        | /    | /    | /    |
        |/     |/     |/     |
        +------+------+------+
       p1      p3     p5     p7 p8
       p9     /|     /|     /|
        |    / |    / |    / |
        |   /  |   /  |   /  |
        |  /   |  /   |  /   |
        | /    | /    | /    |
        |/     |/     |/     |
        +------+------+------+
       p10      p9     p10    p11
    */
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glFrontFace(GL_CW);
    glBegin(GL_TRIANGLE_STRIP);
    for(long unsigned int i = 0; i < heightmap.size()-1; ++i)
    {
        for(long unsigned int j = 0; j < heightmap[i].size(); ++j)
        {
            glVertex3f(x_offset + j, heightmap[i][j], z_offset + i);
            glVertex3f(x_offset + j, heightmap[i+1][j], z_offset + i+1);
        }
            glVertex3f(x_offset + heightmap[i].size()-1, heightmap[i+1][heightmap[i].size()-1], z_offset + i + 1);
            glVertex3f(x_offset                        , heightmap[i+1][0], z_offset + i + 1);

    }
    glEnd();
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
            glColor3f(0.9f, 0.9f, 0.9f);
            glTranslatef(-pow(2, n)/2, 0, -pow(2, n)/2);
            // std::cout << heightmap << std::endl;
            draw_triangle_mesh(heightmap.heightmap());
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
            double product = sqrt(pow(view.eyex(), 2) + pow(view.eyey(), 2) + pow(view.eyez(), 2));
            view.eyex() -= view.eyex()/(product); 
            view.eyey() -= view.eyey()/(product); 
            view.eyez() -= view.eyez()/(product); 
            reset = true;
        } break;
        case 'N':
        {
            double product = sqrt(pow(view.eyex(), 2) + pow(view.eyey(), 2) + pow(view.eyez(), 2));
            view.eyex() += view.eyex()/(product); 
            view.eyey() += view.eyey()/(product); 
            view.eyez() += view.eyez()/(product); 
            reset = true;
        } break;

        case '-': n -= 1; heightmap = heightmap.resize(n); heightmap.Diamond_Square(roughness); reset = true; break;
        case '+': n += 1; heightmap = heightmap.resize(n); heightmap.Diamond_Square(roughness); reset = true; break;

        case 's': roughness -= 0.1; heightmap.Diamond_Square(roughness); reset = true; break;
        case 'S': roughness += 0.1; heightmap.Diamond_Square(roughness); reset = true; break;

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
