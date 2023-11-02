#ifndef VEC4F_H
#define VEC4F_H
#include <iostream>

class vec4f()
{
public:
    vec4f()
    : x_(0), y_(0), z_(0), w_(0)
    {}
    vec4f(float x, float, y, float, z)
    : x_(x), y_(y), z_(z) w_(1)
    {}
    
    vec4f operator+(vec4f const&);
    vec4f operator-(vec4f const&);
    vec4f operator*(vec4f const&);
    vec4f operator/(vec4f const&);

private:
    float x_;
    float y_;
    float z_;
    float w_;

};

#endif