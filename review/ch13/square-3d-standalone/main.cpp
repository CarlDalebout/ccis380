#include <iostream>
#include <GL/freeglut.h>
#include "gl3d.h"

float eyex;
float eyey;
float eyez;
float refx;
float refy;
float refz;

float left;
float right;
float top;
float bottom;
float zNear;
float zFar;

void init()
{
    eyex = 0.0f;
    eyey = 0.0f;
    eyez = 1.0f;
    refx = 0.0f;
    refy = 0.0f;
    refz = 0.0f;
    left = -5;;
    right = 5;
    top = 5;
    bottom = -5;
    zNear = 0.1;
    zFar = 5;

    // Set view volume for orthographic (parallel) projection
    // (Note: lengths of line segment stays the same, i.e.,
    // lines further away do not appear shorted, i.e., no
    // sense of perspective. This is the case for architectural
    // drawing, engineering CAD drawing, 2D games, isometric
    // games, etc.
    //
    // The 6 values passed to glOrtho() is the clipping volume,
    // i.e., only objects in this volume are seen.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(left, right,  
            bottom, top,
            zNear, zFar);    

    // Set camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyex, eyey, eyez, // eye position (eyex, eyey, eyez)
              refx, refy, refz, // eye look at (refx, refy, refz)
              0.0, 1.0, 0.0);   // eye up direction x,y,z    
    
    glViewport(0, 0, 400, 400);

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    mygllib::draw_xz_plane();
    mygllib::draw_axes();

    // glBegin(GL_QUADS);
    // {
    //     glColor3f(1,0,0); glVertex3f(0,-2,0);
    //     glColor3f(0,1,0); glVertex3f(1,0,0);
    //     glColor3f(0,0,1); glVertex3f(1,1,0);
    //     glColor3f(0,0,0); glVertex3f(0,1,0);
    // }
    // glEnd();

    /* SECOND RUN
    glPushMatrix();
    glTranslatef(3, 0, 0);
    glBegin(GL_QUADS);
    {
        glColor3f(1,0,0); glVertex3f(0,0,0);
        glColor3f(0,1,0); glVertex3f(1,0,0);
        glColor3f(0,0,1); glVertex3f(1,1,0);
        glColor3f(0,0,0); glVertex3f(0,1,0);
    }
    glEnd();
    glPopMatrix();
    */
    
    // /* THIRD RUN
    glPushMatrix();
    glTranslatef(3, 0, 0); 
    glScalef(0.5, 2, 1);   // what if you swap translate and scale?
    glBegin(GL_QUADS);
    {
        glColor3f(1,0,0); glVertex3f(0,0,0);
        glColor3f(0,1,0); glVertex3f(1,0,0);
        glColor3f(0,0,1); glVertex3f(1,1,0);
        glColor3f(0,0,0); glVertex3f(0,1,0);
    }
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-3, 0, 0); 
    glScalef(0.5, 2, 1);   // what if you swap translate and scale?
    glBegin(GL_QUADS);
    {
        glColor3f(1,0,0); glVertex3f(0,0,0);
        glColor3f(0,1,0); glVertex3f(1,0,0);
        glColor3f(0,0,1); glVertex3f(1,1,0);
        glColor3f(0,0,0); glVertex3f(0,1,0);
    }
    glEnd();
    glPopMatrix();
    
    // */

    /* FOURTH RUN
    glPushMatrix();
    glTranslatef(3, 0, 0); 
    glRotatef(45, 0, 0, 1);  
    glBegin(GL_QUADS);
    {
        glColor3f(1,0,0); glVertex3f(0,0,0);
        glColor3f(0,1,0); glVertex3f(1,0,0);
        glColor3f(0,0,1); glVertex3f(1,1,0);
        glColor3f(0,0,0); glVertex3f(0,1,0);
    }
    glEnd();
    glPopMatrix();
    */
    
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
        case 'x': eyex -= 0.1; break;
        case 'X': eyex += 0.1; break;
        case 'y': eyey -= 0.1; break;
        case 'Y': eyey += 0.1; break;
        case 'z': eyez -= 0.1; break;
        case 'Z': eyez += 0.1; break;
            
        case 'l': left -= 0.1; break;
        case 'L': left += 0.1; break;
        case 'r': right -= 0.1; break;
        case 'R': right += 0.1; break;
        case 't': top -= 0.1; break;
        case 'T': top += 0.1; break;
        case 'b': bottom -= 0.1; break;
        case 'B': bottom += 0.1; break;
        case 'n': zNear -= 0.1; break;
        case 'N': zNear += 0.1; break;
        case 'f': zFar -= 0.1; break;
        case 'F': zFar += 0.1; break;
    }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();//sets the matrix to the identity matrix
    glOrtho(left, right,  
            bottom, top,
            zNear, zFar);    

    // The setting of eye is controlled by the keyboard, so
    // can put the gluLookAt() here
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); //sets the matrix to the identity matrix
    gluLookAt(eyex, eyey, eyez,
              refx, refy, refz,
              0.0, 1.0, 0.0);

    glutPostRedisplay();
}

int main(int argc, char ** argv)
{
    glutInit(&argc, argv);    
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutCreateWindow("OpenGL!!!");
  
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
  
    return 0;
}
