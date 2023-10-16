#include <iostream>
#include <string>
#include "Mat.h"

int main()
{
    float x[] = {2 ,0, 1, 0,
                  3, 1, 3, 0,
                  1, 2, 0, 1,
                  1, 0, 1, 1};

    float y[] = {1, 0, 0,
                 0, 0, 1,
                 0, 1, 0};

    Mat<float> m(4, 4, x);
    Mat<float> n(3, 3, y);
    std::cout << m << std::endl;
    try
    {
        std::cout << m.adj() << m.det() << "\n\n";
        std::cout << m.inverse() << std::endl;
        std::cout << (m *= m.inverse()) << std::endl;
    }
    catch(IndexError & e)
    {
        e.print_error_code();
    }
    catch(SizeError & e)
    {
        e.print_error_code();
    }
    

    
    return 0;
}