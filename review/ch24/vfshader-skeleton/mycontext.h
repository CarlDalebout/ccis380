#ifndef MYINITCONTEXT_H
#define MYINITCONTEXT_H

namespace mygllib
{
    void myinitContext()
    {
        GLenum err;
        glutInitContextVersion(3, 3);
        //glutInitContextProfile(GLUT_CORE_PROFILE);
        glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
        DEBUG();
        
        int major, minor;
        glGetIntegerv(GL_MAJOR_VERSION, &major);
        glGetIntegerv(GL_MINOR_VERSION, &minor);
        std::cout << "OpenGL " << major << '.' << minor << '\n';
    }
}

#endif
