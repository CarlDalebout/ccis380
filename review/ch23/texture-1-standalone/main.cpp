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

#include "ImageFile.h"

mygllib::Light light;
int y_axis_angle = 0;
GLuint texture[3];        // array of texture indices
float yangle = 0.0;       // angle about y-axis to rotate textured square
float xangle = 0.0;       // angle about x-axis to rotate textured square
int id = 0;               // currently displayed texture id

int env = 0;

void load_external_texture(GLuint texid,
                           const std::string & filename)
{
    // Select texture id texture[0]
    glBindTexture(GL_TEXTURE_2D, texid); 
    
    // Set texture parameters for wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    // Set texture parameters for filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    // Load image data into texture
    BMPFile image(filename);
    glTexImage2D(GL_TEXTURE_2D,
                 0,                // level of detail
                 GL_RGB,           // texture image format
                 image.width(),    // image width
                 image.height(),   // image height
                 0,              
                 GL_RGB,           // image format (same as
                                   // texture image format)
                 GL_UNSIGNED_BYTE, // type for image data
                 image.data());    // address of image
}


// Create 64 x 64 RGB image of a chessboard.
void create_chessboard(GLubyte chessboard[64][64][3])
{
   for (int i = 0; i < 64; i++)
   {
      for (int j = 0; j < 64; j++)
      {
          if ((((i >> 3) & 1) & ((j >> 3) & 1))
              || (!((i >> 3) & 1) & !((j >> 3) & 1)))
          {
              chessboard[i][j][0] = 0x00;
              chessboard[i][j][1] = 0x00;
              chessboard[i][j][2] = 0x00;
          }
          else
          {
              chessboard[i][j][0] = 0xFF;
              chessboard[i][j][1] = 0xFF;
              chessboard[i][j][2] = 0xFF;
          }
      }
   }
}


// Routine to load a program-generated image as a texture.
void load_procedural_textures(GLuint texid, void * const p)
{
    // Select texture id texture[1]. 
    glBindTexture(GL_TEXTURE_2D, texid); 

    // Set texture parameters for wrapping.    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Set texture parameters for filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Load image data into texture
    glTexImage2D(GL_TEXTURE_2D,
                 0, GL_RGB, 64, 64, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, (GLubyte *) p);
}


void init(void)
{
    mygllib::View & view = *(mygllib::SingletonView::getInstance());
    view.eyex() = 0.0f;
    view.eyey() = 1.0f;
    view.eyez() = 10.0f;
    view.zNear() = 0.1;
    view.lookat();
    
    glClearColor(1, 1, 1, 0);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);

    mygllib::Light::all_on();
    light.on();

    glGenTextures(3, texture);  // Create texture index array.
    glEnable(GL_TEXTURE_2D);    // Turn on OpenGL 2D texturing.

    // Create texture from image file
    // Or "images/launch.bmp"
    load_external_texture(texture[0], "images/rock-taupe.bmp");
    load_external_texture(texture[1], "images/nightSky.bmp");

    //Create texture procedurally
    GLubyte chessboard[64][64][3];
    create_chessboard(chessboard);
    load_procedural_textures(texture[2], chessboard); 
    
    // Specify how texture values combine with current surface
    // color values. In this case, the texture data replaces what's
    // the pixel data.
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); 
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    {
        glRotatef(y_axis_angle, 0, 1, 0);
        mygllib::Light::all_off();
        glDisable(GL_TEXTURE_2D);
        mygllib::draw_xz_plane();
        mygllib::draw_axes();
        mygllib::Light::all_on();
        glEnable(GL_TEXTURE_2D);
                     
        glRotatef(xangle, 1.0, 0.0, 0.0); 
        glRotatef(yangle, 0.0, 1.0, 0.0); 
    
        // Select texture with id texture[id]
        glBindTexture(GL_TEXTURE_2D, texture[id]);

        // Choose GL_REPLACE or GL_MODULATE
        if (env == 0)
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        else
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
        glBegin(GL_POLYGON);
        {
            //glColor3f(0, 1, 0); //??
            glTexCoord2f(0.0, 0.0); glVertex3f(-5.0, -5.0, 0.0);
            glTexCoord2f(1.0, 0.0); glVertex3f( 5.0, -5.0, 0.0);
            glTexCoord2f(1.0, 1.0); glVertex3f( 5.0,  5.0, 0.0);
            glTexCoord2f(0.0, 1.0); glVertex3f(-5.0,  5.0, 0.0);
        }
        glEnd();
        
        // 2nd run: replace 1.0 by 0.5 from 1st run
        /*
        glBegin(GL_POLYGON);
        {
            glTexCoord2f(0.0, 0.0); glVertex3f(-5.0, -5.0, 0.0);
            glTexCoord2f(0.5, 0.0); glVertex3f( 5.0, -5.0, 0.0);
            glTexCoord2f(0.5, 0.5); glVertex3f( 5.0,  5.0, 0.0);
            glTexCoord2f(0.0, 0.5); glVertex3f(-5.0,  5.0, 0.0);
        }
        glEnd();
        */

        // 3rd run: last line of 1st run removed
        /*
        glBegin(GL_POLYGON);
        {
            glTexCoord2f(0.0, 0.0); glVertex3f(-5.0, -5.0, 0.0);
            glTexCoord2f(1.0, 0.0); glVertex3f( 5.0, -5.0, 0.0);
            glTexCoord2f(1.0, 1.0); glVertex3f( 5.0,  5.0, 0.0);
        }
        glEnd();
        */
        
        // 4th run: last line of 1st run removed
        /*
        glBegin(GL_POLYGON);
        {
            glTexCoord2f(0.0, 0.0); glVertex3f(-5.0, -5.0, 0.0);
            glTexCoord2f(1.0, 0.0); glVertex3f( 5.0, -5.0, 0.0);
            glTexCoord2f(1.0, 1.0); glVertex3f( 0.0,  5.0, 0.0);
        }
        glEnd();
        */
        
        // 5th run: last line of 1st run removed
        /*
        glBegin(GL_POLYGON);
        {
            glTexCoord2f(0.0, 0.0); glVertex3f(-5.0, -5.0, 0.0);
            glTexCoord2f(1.0, 0.0); glVertex3f( 5.0, -5.0, 0.0);
            glTexCoord2f(1.0, 1.0); glVertex3f(-5.0,  5.0, 0.0);
        }
        glEnd();
        */

        // 6th run: Repeats. The coordinates in the (s,t) space is
        // outside [0,1]x[0,1]
        /*
        glBegin(GL_POLYGON);
        {
            glTexCoord2f(-1.0, 0.0); glVertex3f(-5.0, -5.0, 0.0);
            glTexCoord2f(2.0, 0.0);  glVertex3f( 5.0, -5.0, 0.0);
            glTexCoord2f(2.0, 2.0);  glVertex3f( 5.0,  5.0, 0.0);
            glTexCoord2f(-1.0, 2.0); glVertex3f(-5.0,  5.0, 0.0);
        }
        glEnd();
        */

        // 7th run: Why?
        /*
        glBegin(GL_POLYGON);
        {
            glTexCoord2f(-1.5, 0.0); glVertex3f(-5.0, -5.0, 0.0);
            glTexCoord2f(2.0, 0.0);  glVertex3f( 5.0, -5.0, 0.0);
            glTexCoord2f(2.0, 2.0);  glVertex3f( 5.0,  5.0, 0.0);
            glTexCoord2f(-1.0, 2.0); glVertex3f(-5.0,  5.0, 0.0);
        }
        glEnd();
        */

        // 8th run: Why?
        /*
        glBegin(GL_POLYGON);
        {
            glTexCoord2f(0.0, 0.0); glVertex3f(-5.0, -5.0, 0.0);
            glTexCoord2f(1.0, 0.0); glVertex3f( 5.0, -5.0, 0.0);
            glTexCoord2f(1.0, 1.0); glVertex3f( 5.0,  5.0, 0.0);
            glTexCoord2f(0.0, 1.0); glVertex3f(-5.0,  5.0, 0.0);
            glTexCoord2f(0.0, 1.0); glVertex3f(-5.0,  0.0, 0.0);
        }
        glEnd();
        */
    }
    glPopMatrix();
    glutSwapBuffers();	
}


void keyboard(unsigned char key, int x, int y)
{
    mygllib::View & view = *(mygllib::SingletonView::getInstance());
    bool reset = false;
    switch(key) 
    {
        case 'x': view.eyex() -= 0.1; reset = true; break;
        case 'X': view.eyex() += 0.1; reset = true; break;
        case 'y': view.eyey() -= 0.1; reset = true; break;
        case 'Y': view.eyey() += 0.1; reset = true; break;
        case 'z': view.eyez() -= 0.1; reset = true; break;
        case 'Z': view.eyez() += 0.1; reset = true; break;
            
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

        case 'r': y_axis_angle += 1; reset = true; break;
        case 'R': y_axis_angle -= 1; reset = true; break;
        
        case '1': light.x() += 0.1; reset = true; break;
        case '2': light.x() -= 0.1; reset = true; break;
        case '3': light.y() += 0.1; reset = true; break;
        case '4': light.y() -= 0.1; reset = true; break;
        case '5': light.z() += 0.1; reset = true; break;
        case '6': light.z() -= 0.1; reset = true; break;
    
        case ' ':
            ++id; id = (id > 2 ? 0 : id);
            reset = true;
            break;
        case 127: // delete key
            xangle = 0.0;
            yangle = 0.0;
            reset = true;
            break;

        case 'e':
            env = (env == 0 ? 1 : 0);
            reset = true;
            break;
        default:
            break;
    }
    if (reset)
    {
        view.lookat();
        glutPostRedisplay();
    }
}


void specialkeyboard(int key, int x, int y)
{
    mygllib::View & view = *(mygllib::SingletonView::getInstance());
    bool reset = false;
    switch (key)
    {
        case GLUT_KEY_LEFT:
            yangle -= 5.0;
            if (yangle < 0.0) yangle += 360.0;
            reset = true;
            break;
        case GLUT_KEY_RIGHT: 
            yangle += 5.0;
            if (yangle > 360.0) yangle -= 360.0;
            reset = true;
            break;
        case GLUT_KEY_UP:
            xangle -= 5.0;
            if (xangle < 0.0) xangle += 360.0;
            reset = true;
            break;
        case GLUT_KEY_DOWN: 
            xangle += 5.0;
            if (xangle > 360.0) xangle -= 360.0;
            reset = true;
            break;
    }
    if (reset)
    {
        view.lookat();
        glutPostRedisplay();
    }
}


int main(int argc, char **argv) 
{
    std::cout << "left/right arrow: rotate" << '\n'
              << "space: toggle textures" << '\n'
              << "delete: reset" << '\n';
    
    mygllib::init3d();
    init();
    
    glutDisplayFunc(display);
    glutReshapeFunc(mygllib::Reshape::reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialkeyboard);
    glutMainLoop();
    
    return 0; 
}
