#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "mvp.h"

extern glm::vec3 eye, ref, up;

inline
void keyboard(unsigned char key, int x, int y)
{
    std::cout << "key:" << key << '\n';
    bool reset = false;
    switch (key)
    {
        case 'x':
            reset = true;
            eye.x -= 0.1;
            break;
        case 'X':
            reset = true;
            eye.x += 0.1;
            break;
        case 'y':
            reset = true;
            eye.y -= 0.1;
            break;
        case 'Y':
            reset = true;
            eye.y += 0.1;
            break;
        case 'z':
            reset = true;
            eye.z -= 0.1;
            break;
        case 'Z':
            reset = true;
            eye.z += 0.1;
            break;
        case 'r':
            reset = true;
            umodel = glm::rotate(umodel, -5.0f * 3.14f/180.0f,
                                 glm::vec3(1, 0, 0)); // rotate about x-axis
            break;
        case 'R':
            reset = true;
            umodel = glm::rotate(umodel, 5.0f * 3.14f/180.0f,
                                 glm::vec3(1, 0, 0)); // rotate about x-axis
            break;
        case 's':
            reset = true;
            umodel = glm::rotate(umodel, -5.0f * 3.14f/180.0f,
                                 glm::vec3(0, 1, 0)); // rotate about y-axis
            break;
        case 'S':
            reset = true;
            umodel = glm::rotate(umodel, 5.0f * 3.14f/180.0f,
                                 glm::vec3(0, 1, 0)); // rotate about y-axis
            break;
        case 't':
            reset = true;
            umodel = glm::rotate(umodel, -5.0f * 3.14f/180.0f,
                                 glm::vec3(0, 0, 1)); // rotate about z-axis
            break;
        case 'T':
            reset = true;
            umodel = glm::rotate(umodel, 5.0f * 3.14f/180.0f,
                                 glm::vec3(0, 0, 1)); // rotate about z-axis
            break;
    }
    if (reset)
    {
        uview = glm::lookAt(eye, ref, up);
        glutPostRedisplay();
    }
}

#endif

