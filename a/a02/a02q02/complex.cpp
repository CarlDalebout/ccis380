#include <cmath>
#include "complex.h"

double complex::re() const
{
    return re_;
}
double complex::im() const
{
    return im_;
}

complex & complex::operator+=(const complex & z)
{
    complex temp0 = *this;
    complex temp1 = z;
    *this = temp0 + temp1;
    return *this;
}   
complex & complex::operator-=(const complex & z)
{
    complex temp0 = *this;
    complex temp1 = z;
    *this = temp0 - temp1;
    return *this;
}
complex & complex::operator*=(const complex & z)
{  
    complex temp0 = *this;
    complex temp1 = z;
    *this = temp0 * temp1;
    return *this;
}
complex & complex::operator/=(const complex & z)
{
    complex temp0 = *this;
    complex temp1 = z;
    *this = temp0 / temp1;
    return *this;
}



complex complex::operator+(const complex & z) const
{
    return complex((re_ + z.re()), (im_ + z.im()));
}
complex complex::operator-(const complex & z)
{
    return complex((re_ - z.re()), (im_ - z.im()));
}
complex complex::operator*(const complex & z)
{
    return complex( ( (re_ * z.re()) - (im_ * z.im()) ), ( (re_ * z.im()) + (im_ * z.re()) ));
}
complex complex::operator/(const complex & z) const
{   
    complex temp1( (re_ / (pow(z.re(), 2) + pow(z.im(), 2))), (im_ / (pow(z.re(), 2) + pow( z.im(), 2))) );
    complex temp2(z.re(), -z.im());
    return complex(temp1 * temp2);
}   
complex complex::pow2()
{
    re_ = (re_ * re_) - (im_ * im_);
    im_ = im_ * im_;
}
double complex::abs() const
{
    return sqrt(pow(re_, 2) + pow(im_, 2));
}


complex operator+(double x, const complex & z)
{
    return complex((x + z.re()), (z.im()));
}
complex operator-(double x, const complex & z)
{
    return complex((x - z.re()), (z.im()));
}
complex operator*(double x, const complex & z)
{
    return complex( (x * z.re()), (x * z.im()) ) ;
}
complex operator/(double x, const complex & z)
{
    complex temp1( ( x / (pow(z.re(), 2) + pow(z.im(), 2))) , 0 );
    complex temp2( z.re(), -z.im());
    return temp1 * temp2;
}
double abs(const complex z)
{
    return sqrt(pow(z.re(), 2) + pow(z.im(), 2));
}
std::istream & operator>>(std::istream & cin, complex & z)
{
    double re, im;
    cin >> re >> im;
    complex temp(re, im);
    z = temp;
    return cin;
}
std::ostream & operator<<(std::ostream & cout, complex const & z)
{
    if(z.im() >= 0)
        cout << z.re()  << " + " << z.im() << 'i';
    else
        cout << z.re() << " - " << -z.im() << 'i';
    return cout;
}
