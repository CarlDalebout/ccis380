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
#include "Text.h"

/*
                y
                
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
         
       z

       4-----5
       |     |
       | TOP |
       |     |
       0-----1-----5-----4-----0
       |     |     |     |     |
       |FRONT|RIGHT|BACK |LEFT |
       |     |     |     |     |
       3-----2-----6-----7-----3
       |     |
       |BOTTO|
       |M    |
       7-----6                        
                                     
                                     
       vertices: 4,0,5,1, 1,0, 0,3,1,2,5,6,4,7,0,3, 3,3, 3,7,2,6
       normals   2 2 2 2  2 2  4 4 4 4 0 0 5 5 1 1  1 3  3 3 3,3
                     ^                 ^ 
                     |                 | 
                     +-----------------+
                     these two p5 have different normals j,i
       where
       normals are i,-i, j,-j, k,-k
                   0, 1, 2, 3, 4, 5

       NOTE: The above is OK for smooth shading.
       For sharp edges treat adjacent faces as separate strips.

       vertices: 4,0,5,1  1,0  0,3,1,2  2,1  1,2,5,6  6,5  5,6,4,7  7,4  4,7,0,3  3,3, 3,7,2,6
       normals   2 2 2 2       4 4 4 4       0,0,0 0       5,5,5,5       1,1,1,1       3,3,3,3

       34 vertex-normal pairs = 34 x 6 x 4 = 816 bytes

       Omitting degenerate repeats 24 x 6 x 4 = 576 bytes
       Indices (size 34)                      =  34 bytes
       Total                                  = 610 bytes

       Data:
       0,1,0, 0,1,0,  // 4 (top)
       0,1,1, 0,1,0,  // 0 (top)
       1,1,0, 0,1,0,  // 5 (top)
       1,1,1, 0,1,0,  // 1 (top)
                                 
       0,1,1, 0,0,1,  // 0 (front)
       0,0,1, 0,0,1,  // 3 (front)
       1,1,1, 0,0,1,  // 1 (front)
       1,0,1, 0,0,1,  // 2 (front)                        

       1,1,1, 1,0,0,  // 1 (right)
       1,0,1, 1,0,0,  // 2 (right) 
       1,1,0, 1,0,0,  // 5 (right)
       1,0,0, 1,0,0,  // 6 (right)

       1,1,0, 0,0,-1, // 5 (back)
       1,0,0, 0,0,-1, // 6 (back)
       0,1,0, 0,0,-1, // 4 (back)
       0,0,0, 0,0,-1, // 7 (back)

       0,1,0, -1,0,0, // 4 (left)
       0,0,0, -1,0,0, // 7 (left)
       0,1,1, -1,0,0, // 0 (left)
       0,0,1, -1,0,0, // 3 (left)

       0,0,1, 0,-1,0, // 3 (bottom)
       0,0,0, 0,-1,0, // 7 (bottom)
       1,0,1, 0,-1,0, // 2 (bottom)
       1,0,0, 0,-1,0  // 6 (botoom)
*/

GLfloat RED[] = {1, 0, 0};

enum { IMMED_QUADS,
       IMMED_TRI_MESH,
       CLIENT_SIDE_VERTEX_ARRAY_GLDRAWARRAYS,
       CLIENT_SIDE_VERTEX_ARRAY_GLDRAWELEMENTS,
       DISPLAY_LIST };
char labels[][50] = {"immed quads",
                     "immed tri-mesh",
                     "client-side vert arr gldrawarrays",
                     "client-side vert arr gldrawelements",
                     "display list"};
int option = IMMED_QUADS;

mygllib::Light light;
GLfloat light_model_ambient[] = {1.0, 1.0, 1.0, 1.0};

int x_axis_angle = 0;
int y_axis_angle = 0;
int z_axis_angle = 0;

int cube = 0; // display list id

static GLfloat p[] = {0, 1, 1, //
                      1, 1, 1,
                      1, 0, 1,
                      0, 0, 1,
                      0, 1, 0,
                      1, 1, 0,
                      1, 0, 0,
                      0, 0, 0};
static GLfloat *p0 = p;
static GLfloat *p1 = &p[3];
static GLfloat *p2 = &p[6];
static GLfloat *p3 = &p[9];
static GLfloat *p4 = &p[12];
static GLfloat *p5 = &p[15];
static GLfloat *p6 = &p[18];
static GLfloat *p7 = &p[21];
//static GLfloat p0[] = {0, 1, 1};
//static GLfloat p1[] = {1, 1, 1};
//static GLfloat p2[] = {1, 0, 1};
//static GLfloat p3[] = {0, 0, 1};
//static GLfloat p4[] = {0, 1, 0};
//static GLfloat p5[] = {1, 1, 0};
//static GLfloat p6[] = {1, 0, 0};
//static GLfloat p7[] = {0, 0, 0};


void init()
{
    mygllib::View * view = mygllib::SingletonView::getInstance();
    view->eyex() = 2.5f;
    view->eyey() = 1.5f;
    view->eyez() = 3.0f;
    view->zNear() = 0.1f;
    view->lookat();    

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    
    mygllib::Light::all_on();
    light.on();
    light.set();
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_model_ambient);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
}


void draw_cube_immed_quads()
{
    glFrontFace(GL_CCW); 
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glBegin(GL_QUADS);
    {
        // front 
        glNormal3f(0, 0, 1); 
        glVertex3fv(p3); glVertex3fv(p2); glVertex3fv(p1); glVertex3fv(p0);

        // back
        glNormal3f(0, 0, -1);
        glVertex3fv(p6); glVertex3fv(p7); glVertex3fv(p4); glVertex3fv(p5);
        
        //left
        glNormal3f(-1, 0, 0);
        glVertex3fv(p7); glVertex3fv(p3); glVertex3fv(p0); glVertex3fv(p4);

        //right
        glNormal3f(1, 0, 0);
        glVertex3fv(p2); glVertex3fv(p6); glVertex3fv(p5); glVertex3fv(p1);

        //top
        glNormal3f(0, 1, 0);
        glVertex3fv(p0); glVertex3fv(p1); glVertex3fv(p5); glVertex3fv(p4);

        //bottom
        glNormal3f(0, -1, 0);
        glVertex3fv(p7); glVertex3fv(p6); glVertex3fv(p2); glVertex3fv(p3);
    }
    glEnd();
}


void create_display_list_cube()
{
    // display list using glDrawArrays

    // TODO
    glFrontFace(GL_CCW); 
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}


void draw_cube_tri_mesh()
{
    glFrontFace(GL_CCW); 
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glBegin(GL_TRIANGLE_STRIP);
    {
        // TODO
    }
    glEnd();
}


void draw_cube_client_side_vertex_array_gldrawarrays()
{
    // TODO
    glFrontFace(GL_CCW); 
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}


void draw_cube_client_side_vertex_array_gldrawelements()
{
    // TODO
    glFrontFace(GL_CCW); 
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mygllib::Light::all_off();
    mygllib::draw_axes();
    mygllib::draw_xz_plane();
    
    glPushMatrix();
    {
        glRotatef(x_axis_angle, 1, 0, 0);
        glRotatef(y_axis_angle, 0, 1, 0);
        glRotatef(z_axis_angle, 0, 0, 1);

        glColor3fv(RED);
        mygllib::Text::draw(labels[option], 0, 1.5, 0);

        mygllib::Light::all_on();
        mygllib::Material mat(mygllib::Material::CYAN_PLASTIC);
        mat.set();
        switch (option)
        {
            case IMMED_QUADS:
                draw_cube_immed_quads();
                break;
            case IMMED_TRI_MESH:
                draw_cube_tri_mesh();
                break;
            case CLIENT_SIDE_VERTEX_ARRAY_GLDRAWARRAYS:
                draw_cube_client_side_vertex_array_gldrawarrays();
                break;
            case CLIENT_SIDE_VERTEX_ARRAY_GLDRAWELEMENTS:    
                draw_cube_client_side_vertex_array_gldrawelements();
                break;
            case DISPLAY_LIST:
                glCallList(cube);
                break;
        }
    }
    glPopMatrix();
    glutSwapBuffers();
}


void keyboard(unsigned char key, int x, int y)
{
    mygllib::View * view = mygllib::SingletonView::getInstance();
    bool reset = false;

    switch (key)
    {
        case 'w': // which
            option = (option + 1) % 5;
            reset = true;
            break;
            
        case 'x': view->eyex() += 0.1; reset = true; break;
        case 'X': view->eyex() -= 0.1; reset = true; break;
        case 'y': view->eyey() += 0.1; reset = true; break;
        case 'Y': view->eyey() -= 0.1; reset = true; break;
        case 'z': view->eyez() += 0.1; reset = true; break;
        case 'Z': view->eyez() -= 0.1; reset = true; break;
            
        case 'r': x_axis_angle += 2; reset = true; break;
        case 'R': x_axis_angle -= 2; reset = true; break;
        case 's': y_axis_angle += 2; reset = true; break;
        case 'S': y_axis_angle -= 2; reset = true; break;
        case 't': z_axis_angle += 2; reset = true; break;
        case 'T': z_axis_angle -= 2; reset = true; break;
        
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
        view->lookat();
        light.set();
        glutPostRedisplay();
    }
}


int main(int argc, char ** argv)
{
    std::cout << "eye control: x,X,y,Y,z,Z,R\n"; 
    std::cout << "light control: 1,2,3,4,5,6\n";
    std::cout << "rotate model: r,R,s,S,t,T\n";
    std::cout << "toggle between models: o\n";
    std::cout << "see keyboard function for details\n";
    
    mygllib::init3d();
    init();
    create_display_list_cube();
    
    glutDisplayFunc(display);
    glutReshapeFunc(mygllib::Reshape::reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    
    return 0;
}
