#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <stdlib.h>
#include <string>

const int SIZE = 12;

void randarray(char m[SIZE][SIZE], int r, int C)
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < C; j++)
        {
            m[i][j] = (int(rand() % 6)-2);
        }
    }
}

//=============================================================================
// Print 2D array.
//=============================================================================
void printarray(char m[SIZE][SIZE], int r, int c)
{
    for (int i = 0; i < r; i++)
    {
        std::string dir = "";
        for (int j = 0; j < c; j++)
        {
            std::cout << std::setw(0) << dir << std::setw(2) << std::setfill('+') << int(m[i][j]);
            dir = " | ";
        }
        std::cout << '\n';
    }
}

struct subarray
{
    int x_ = 0;
    int y_ = 0; 
    int rows_ = 0;
    int coloms_ = 0;
};

subarray fixmax(char m[SIZE][SIZE], int r, int c)
{
    int max_sum = int(m[0][0]);
    subarray max_sub;
    std::cout << max_sum << std::endl;    

    for(int i = 0; i < r; ++i)
    {
        
    }

    return max_sub;
}

std::ostream & operator<<(std::ostream & cout, const subarray & z)
{
    cout << z.x_ << ' ' << z.y_ << ' ' << z.rows_ << ' ' << z.coloms_;
    return cout;
}

int main()
{
    int seed, r, c;
    std::cin >> seed >> r >> c;
    srand(seed);
    char m[SIZE][SIZE];
    randarray(m, r, c);
    printarray(m, r, c);
    std::cout << '\n' << fixmax(m, r, c) << std::endl;
    return 0;
}