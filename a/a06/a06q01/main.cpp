#include <iostream>
#include "Mat.h"

int main()
{
    int x[] = {1, 2, 3, 4};
    Mat<int> m(2, 2, x);
    m(1, 1) = 5;
    for(int i = 0; i < m.rowsize(); ++i)
    {
        for(int j = 0; j < m.colsize(); ++j)
        {
            std::cout << m(i, j) << std::endl;
        }
    }
    return 0;
}