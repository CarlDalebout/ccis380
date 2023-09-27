#include <iostream>
#ifndef COMPLEX_H
#define COMPLEX_H

class complex
{
public:
    complex()
        : re_(0), im_(0)
    {}

    complex(double re, double im)
        : re_(re), im_(im)
    {}

    double re() const;
    double im() const;

    const complex & operator+=(const complex & z);
    const complex & operator-=(const complex & z);
    const complex & operator*=(const complex & z);
    const complex & operator/=(const complex & z);
    complex operator+(const complex & z) const;
    complex operator-(const complex & z);
    complex operator*(const complex & z);
    complex operator/(const complex & z) const;
    double abs() const;

private:
    double re_, im_;
};

complex operator+(double x, const complex & z);
complex operator-(double x, const complex & z);
complex operator*(double x, const complex & z);
complex operator/(double x, const complex & z);
double abs(const complex z);
std::istream & operator>>(std::istream & cout, complex & z);
std::ostream & operator<<(std::ostream & cout, const complex & z);

#endif