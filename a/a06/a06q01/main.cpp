#include <iostream>
#include <string>
#include "Mat.h"

int main()
{
    float x[] = {1.1, 2.2, 3.3, 4.4};
    Mat<float> m(2, 2, x);
    m(1, 1) = 5.5;
    float y = m(1, 1);
    try
    {
        y = m(2, 3);
    }
    catch(IndexError & e)
    {
        e.print_error_code();
    }
    std::cout << y << std::endl;
    for(int r = 0; r < m.rowsize(); ++r)
    {
        std::string der = "";
        std::cout << "|";
        for(int c = 0; c < m.colsize(); ++c)
        {
            std::cout << der <<m(r, c); der = ", "; 
        }
        std::cout << "|\n";
    }
    return 0;
}