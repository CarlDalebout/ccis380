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

vec4f vec4f::operator*(vec4f const & vector)
{
    vec4f ret((y_* vector.z_ - (vector.y_ * z_)), 
              (-1* ((x_ * vector.z_) - (vector.x_ * z_))), 
              (x_ * vector.y_) - (vector.x_ * y_));
    return ret;
}

vec4f operator*(vec4f const& vector1, vec4f const& vector2)
{
    vec4f ret((vector1.y()* vector2.z() - (vector2.y() * vector1.z())), 
              (-1* ((vector1.x() * vector2.z()) - (vector2.x() * vector1.z()))), 
              (vector1.x() * vector2.y()) - (vector2.x() * vector1.y()));
    return ret;
}