#ifndef MYSHADER_H
#define MYSHADER_H

#include <GL/glew.h> 
#include <GL/freeglut.h>
#include "myfile.h"

GLuint init_shader(GLenum shader_type, const char filename[])
{
    const int MAX_BUF = 10000;
    const char * buf = new char[MAX_BUF];
    readfile(filename, (char *)buf, MAX_BUF);

    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &buf, NULL);
    glCompileShader(shader);
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char log[1024];
        glGetShaderInfoLog(shader, sizeof(log), NULL, log);
        std::cout << "shader \"" << filename << "\" compilation error(s):\n"
                  << log << std::endl;
        exit(1);
    }
    delete [] buf;
    return shader;
}

GLuint init_shader_program(const char vshader_filename[],
                           const char fshader_filename[])
{    
    GLuint vshader = init_shader(GL_VERTEX_SHADER, vshader_filename);
    GLuint fshader = init_shader(GL_FRAGMENT_SHADER, fshader_filename);
    
    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vshader);
    glAttachShader(shader_program, fshader);
    glLinkProgram(shader_program);
    int success;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        char log[1024];
        glGetProgramInfoLog(shader_program, sizeof(log), NULL, log);
        std::cout << "shader program link error: "
                  << log << std::endl;
        exit(1);
    }
    glDeleteShader(vshader);
    glDeleteShader(fshader);
    return shader_program;
}

inline
GLint get_unif_loc(GLint shader_program, const char name[])
{
    GLint loc = glGetUniformLocation(shader_program, name);
    if (loc == -1)
    {
        std::cout << "glGetUniformLocation warning/error for \"" << name << "\": not found or removed\n";
    }
    return loc;
}

inline
void set_unif(GLint shader_program, const char name[], const glm::vec4 & t)
{
    GLint loc = get_unif_loc(shader_program, name);
    glUniform4fv(loc, 1, glm::value_ptr(t));
}

inline
void set_unif(GLint shader_program, const char name[], const glm::vec3 & t)
{
    GLint loc = get_unif_loc(shader_program, name);
    glUniform3fv(loc, 1, glm::value_ptr(t));
}

inline
void set_unif(GLint shader_program, const char name[], const glm::mat4 & t)
{
    GLint loc = get_unif_loc(shader_program, name);
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(t));
}

inline
void set_unif(GLint shader_program, const char name[], const GLfloat t)
{
    GLint loc = get_unif_loc(shader_program, name);
    glUniform1f(loc, t);
}

#endif
