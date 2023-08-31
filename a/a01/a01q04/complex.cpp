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
    return z;
}
complex & complex::operator-=(const complex & z)
{
    return z;
}
complex & complex::operator*=(const complex & z)
{
    return z;
}
complex & complex::operator/=(const complex & z)
{
    return z;
}
complex complex::operator+(const complex & z) const
{
    return z;
}
complex complex::operator-(const complex & z)
{
    return z;
}
complex complex::operator*(const complex & z)
{
    return z;
}
complex complex::operator/(const complex & z) const
{
    return z;
}
double complex::abs() const
{
    return 1.0;
}


complex operator+(double x, const complex & z)
{
    return z;
}
complex operator-(double x, const complex & z)
{
    return z;
}
complex operator*(double x, const complex & z)
{
    return z;
}
complex operator/(double x, const complex & z)
{
    return z;
}
double abs(const complex z)
{
    return 1.0;
}
std::istream & operator>>(std::istream & cout, complex & z)
{
    return cout;
}
std::ostream & operator<<(std::ostream & cout, const complex & z)
{
    return cout;
}
