#include "all.h"


GLuint vao[1];
GLuint shader_program;
GLuint texture[1];


void load_external_texture(GLuint texid,
                           const std::string & filename)
{
    glActiveTexture(GL_TEXTURE0); // This is the default. So it's not really
                                  // necessary. See chap on textures.
    glBindTexture(GL_TEXTURE_2D, texid);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    BMPFile image(filename);
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGB,
                 image.width(),
                 image.height(),
                 0,
                 GL_RGB,
                 GL_UNSIGNED_BYTE,
                 image.data());
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    //       This is now not necessary since you can do your own fragment
    //       computation in the fragment shader to mix multiple textures.
    glBindTexture(GL_TEXTURE_2D, 0);
}

void init_texture()
{
}


int init_vao()
{
    GLuint vao = 0;
    return vao;
}


void init()
{
    glViewport(0, 0, 400, 400);
    glClearColor(1, 1, 1, 1);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    vao[0] = init_vao();
    //shader_program = init_shader_program("?.vert", "?.frag");

    umodel = glm::mat4(1.0f);
    uview = glm::lookAt(eye, ref, up);
    uproj = glm::perspective(45.0f * 3.14f / 180.0f, 1.0f, 0.1f, 100.0f);
}


void render_vao()
{
    glUseProgram(shader_program);
}


void display()
{    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shader_program);

    //glBindTexture(GL_TEXTURE_2D, texture[0]);
    
    // Set projection, view, model matrix in vertex shader
    set_unif(shader_program, "umodel", umodel);
    set_unif(shader_program, "uview", uview);
    set_unif(shader_program, "uproj", uproj);

    render_vao();
    
    glutSwapBuffers();
}


int main(int argc, char ** argv)
{
    mygllib::init3d();
    mygllib::myinitContext();
    mygllib::myglewInit();

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}
