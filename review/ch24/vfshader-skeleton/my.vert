#version 330 core
layout (location = 0) in vec3 bpos;

out vec3 vpos;

void main()
{
    gl_Position = vec4(bpos, 1.0);    
}
