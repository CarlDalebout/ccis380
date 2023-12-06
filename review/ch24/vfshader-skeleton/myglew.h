#ifndef MYGLEW_H
#define MYGLEW_H

namespace mygllib
{
    void myglewInit()
    {
        glewExperimental = GL_TRUE;
        const GLenum err = glewInit();
        if (err != GLEW_OK)
        {
            std::cout << "glewInit error #" << err << ": "
                      << glewGetErrorString(err) << std::endl;
            exit(1); 
        }
    }
}

#endif
