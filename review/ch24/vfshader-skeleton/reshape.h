#ifndef RESHAPE_H
#define RESHAPE_H

#include "mvp.h"

void reshape(int w, int h)
{
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    float aspect = float(w) / h;
    uview = glm::lookAt(eye, ref, up);
    uproj = glm::perspective(45.0f * 3.14f / 180.0f, aspect, 0.1f, 100.0f);
}

#endif
