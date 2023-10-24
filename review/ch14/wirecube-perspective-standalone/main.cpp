/*
  
  Exercises:
  1. Allow users to increase and decrease various parameters (number of
     rings, radius sizes, etc).
  2. Allow users to rotate objects about different axes.
  3. Allow users to animate rotation and stop animation.
  
 */

#include <GL/freeglut.h>
#include "gl3d.h"
#include "View.h"

mygllib::View view;

int which = 0;

void init()
{
    view.eyex() = 1;
    view.eyey() = 2;
    view.eyez() = 3;
    view.set_projection();
    view.lookat();
    
    glViewport(0, 0, 400, 400);

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
}

float yoffset = 2;
float xoffset = 0;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mygllib::draw_xz_plane();
    mygllib::draw_axes();
    
    glColor3f(0.0f, 0.0f, 1.0f);
    switch (which)
    {
        case 0: 
        {
            glutWireCube(1.0f); 

            glPushMatrix();
            {
                glTranslatef(xoffset, yoffset, 0);
                glColor3f(1, 0, 0);
                glutWireCube(1.0f);
                
                glPushMatrix();
                glTranslatef(0, 1, 0);
                glColor3f(0, 1, 0);
                glutWireCube(1.0f);
                glPopMatrix();

                glPushMatrix();
                glTranslatef(1, 0, 0);
                glColor3f(0, 1, 0);
                glutWireCube(1.0f);
                glPopMatrix();

                glPushMatrix();
                glTranslatef(-1, 0, 0);
                glColor3f(0, 1, 0);
                glutWireCube(1.0f);
                glPopMatrix();
            }
            glPopMatrix(); 
            break;
        }
        case 1: glutWireTorus(0.5, 1.7, 20, 30); break;
        case 2: glutWireTeapot(1.0); break;
        case 3: glutSolidSphere(1.0, 20, 20); break;
        case 4:
        {
            GLUquadricObj * p = gluNewQuadric();
            gluQuadricDrawStyle(p, GLU_LINE);
            // SECOND RUN
            //gluQuadricDrawStyle(p, GLU_FILL);
            float base_radius = 1.0f;
            float top_radius = 0.2f;
            float height = 2.0f;
            int slice_per_ring = 20;
            int rings = 20;
            gluCylinder(p, base_radius, top_radius, height, slice_per_ring, rings);
            gluDeleteQuadric(p);
            break;
        }
        case 5:
        {
            GLUquadricObj * p = gluNewQuadric();
            gluQuadricDrawStyle(p, GLU_LINE);
            float inner_radius = 0.5f;
            float outer_radius = 1.0f;
            int slice_per_ring = 10;
            int rings = 5;
            gluDisk(p, inner_radius, outer_radius, slice_per_ring, rings);
            gluDeleteQuadric(p);
            break;
        }
    }
    
    glutSwapBuffers();
}


void reshape(int w, int h)
{
    glViewport(0, 0, 400, 400);
}


void keyboard(unsigned char key, int x, int y)
{
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

        // shape selection
        case '0': which = 0; break;
        case '1': which = 1; break;
        case '2': which = 2; break;
        case '3': which = 3; break;
        case '4': which = 4; break;
        case '5': which = 5; break;

        //move second cube
        case '+': yoffset += 0.1; break;
        case '-': yoffset -= 0.1; break;
        case '*': xoffset  += 0.1; break;
        case '/': xoffset -= 0.1; break;
    }
    view.set_projection();
    view.lookat();    
    glutPostRedisplay();
}


int main(int argc, char ** argv)
{
    std::cout << "wireframe models from freeglut and glu\n"
              << "0:cube 1:torus 2:teapot 3:sphere 4:cylinder 5:disk\n"
              << "(try dodecahedron and octohedron on your own\n";
    mygllib::init3d();
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
  
    return 0;
}
