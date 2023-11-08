#ifndef BODY_H
#define BODY_H
#include "Vec4f.h"

class Body
{
public:
    Body()
    :mass_(0), position_(), velocity_(), radius_(0)
    {}
    Body(double mass, vec4f p, vec4f v, float radius)
    :mass_(mass), position_(p), velocity_(v), radius_(radius)
    {}
    double & mass()             {return mass_;}
    double   mass()     const   {return mass_;}
    vec4f  & p()                {return position_;}
    vec4f    p()        const   {return position_;}
    vec4f  & v()                {return velocity_;}
    vec4f    v()        const   {return velocity_;}
    float  & radius()           {return radius_;}
    float    radius()   const   {return radius_;}

private:
    double mass_;
    vec4f position_;
    vec4f velocity_;
    float radius_;
};

#endif