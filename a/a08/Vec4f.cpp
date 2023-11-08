#include "Vec4f.h"

vec4f & vec4f::operator=(const vec4f & vector)
{
    x_ = vector.x_;
    y_ = vector.y_;
    z_ = vector.z_;
    w_ = vector.w_;

    return *this;
}

vec4f vec4f::operator+(vec4f const & vector)
{
    vec4f ret(x_ + vector.x_, 
              y_ + vector.y_, 
              z_ + vector.z_, 
              w_ + vector.w_);
    return ret;
}

vec4f vec4f::operator-(vec4f const & vector)
{
    vec4f ret(x_ - vector.x_, 
              y_ - vector.y_, 
              z_ - vector.z_, 
              w_ - vector.w_);
    return ret;
}

vec4f vec4f::operator*(float const scaler)
{
    vec4f ret(x_ * scaler, 
              y_ * scaler, 
              z_ * scaler, 
              w_ * scaler);
    return ret;
}
