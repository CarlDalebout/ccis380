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

int n = 2;
Heightmap heightmap(n);


void init()
{
    mygllib::View & view = *(mygllib::SingletonView::getInstance());
    view.eyex()     = -5.0f;
    view.eyey()     = 10.0f;
    view.eyez()     = 5.0f;
    view.zNear()    = 0.1f;
    view.zFar()     = 50.0f;
    view.aspect()   = 1;
    view.lookat();      

    srand(time(NULL));
    // heightmap.Diamond_Square();
    std::cout << heightmap;

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
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

void draw_triangle_strip(std::vector<float> top, std::vector<float> bottom, float x_offset = 0, float z_offset = 0)
{
    /*
       p0      p2     p3     p5
        +------+------+------+
        |     /|     /|     /|
        |    / |    / |    / |
        |   /  |   /  |   /  |
        |  /   |  /   |  /   |
        | /    | /    | /    |
        |/     |/     |/     |
        +------+------+------+
       p1      p3     p4     p6
    */

    // p0, p1, p2, p3, p4, p5, p6, p7
    // t0 = p0, p1, p2
    // t1 = p2, p1, p3
    // t0 = p3, p4, p5
    {
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glEnable(GL_COLOR_MATERIAL);
        glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
        glFrontFace(GL_CW);
        glBegin(GL_TRIANGLE_STRIP);
        {
            for(long unsigned int i = 0; i < top.size(); ++i)
            {
                glVertex3f(x_offset + i, top[i], z_offset);
                glVertex3f(x_offset + i, bottom[i], z_offset + 1);
            }
        }
        glEnd();
    }
}

void draw_triangle_mesh(std::vector<std::vector<float>> heightmap)
{
    /*
       p0      p1     p2     p3
        +------+------+------+
        |     /|     /|     /|
        |    / |    / |    / |
        |   /  |   /  |   /  |
        |  /   |  /   |  /   |
        | /    | /    | /    |
        |/     |/     |/     |
        +------+------+------+
       p4      p5     p6     p7
        |     /|     /|     /|
        |    / |    / |    / |
        |   /  |   /  |   /  |
        |  /   |  /   |  /   |
        | /    | /    | /    |
        |/     |/     |/     |
        +------+------+------+
       p8      p9     p10    p11
    */
    for(long unsigned int i = 1; i < heightmap.size(); ++i)
    {
        draw_triangle_strip(heightmap[i-1], heightmap[i], 0, i-1);
    }
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
        mygllib::Light::all_on();
        glPushMatrix();
        {
            glColor3f(0.5, 0.5, 0.5);
            // mygllib::Material mat(mygllib::Material::WHITE_PLASTIC);
            // mat.set();
            draw_triangle_mesh(heightmap.heightmap());
        }
        glPopMatrix();
    }
    glPopMatrix();
    glutSwapBuffers();
}

// // Timer Function for glutTimerFunc()
// void animate(int someValue)
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
