#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <stdlib.h>
#include <string>

const int SIZE = 25;

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

//hello git hub

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


int main()
{
    int seed, r, c;
    std::cin >> seed >> r >> c;
    srand(seed);
    char m[SIZE][SIZE];
    randarray(m, r, c);
    printarray(m, r, c);
    return 0;
}