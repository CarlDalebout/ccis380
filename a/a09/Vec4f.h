#ifndef VEC4F_H
#define VEC4F_H
#include <iostream>

class vec4f
{
public:
    vec4f()
    : x_(0), y_(0), z_(0), w_(0)
    {}
    vec4f(float x, float y, float z, float w = 0)
    : x_(x), y_(y), z_(z), w_(w)
    {}
    vec4f & operator=(const vec4f &);
    
    float & x()       { return x_;}
    float   x() const { return x_;}
    float & y()       { return y_;}
    float   y() const { return y_;}
    float & z()       { return z_;}
    float   z() const { return z_;}
    float & w()       { return w_;}
    float   w() const { return w_;}

    vec4f operator+(vec4f const&);
    vec4f operator-(vec4f const&);
    vec4f operator*(float const&);
    vec4f operator*(vec4f const&);
    vec4f operator/(float const&);
private:
    float x_;
    float y_;
    float z_;
    float w_;

};

vec4f operator*(vec4f const&, vec4f const&);

std::istream & operator>>(std::istream& cin , vec4f & vector);
std::ostream & operator<<(std::ostream& cout, const vec4f & vector);

#endif