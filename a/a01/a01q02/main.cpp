#include <iostream>
#include <ctime>
#include <cstdlib>
#include <stdlib.h>
#include <string>
const int SIZE = 20;
const char C[] = {'a', 'b', 'c', 'd', 'e'};

//=============================================================================
// Fill 2D array m with characters chosen randomly from C.
//=============================================================================
void randarray(char m[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            m[i][j] = C[rand() % 5];
        }
    }
}

//=============================================================================
// Print 2D array.
//=============================================================================
void printarray(char m[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            std::cout << m[i][j];
        }
        std::cout << '\n';
    }
}

void sort(std::string & found)
{
    for(int i = found.size(); i > 0; --i)
    {
        for(int j = 0; j < i-1; ++j)
        {
            if(found[j+1] < found[j]) 
            {
                char t = found[j+1];
                found[j+1] = found[j];
                found[j] = t;
            }    
        }
    }
}

bool checkcross(char m[SIZE][SIZE], int i, int j)
{
    std::string found;
    found.insert(found.begin(), m[i][j]); //center
    found.insert(found.begin(), m[i-1][j]); //north
    found.insert(found.begin(), m[i+1][j]); //south
    found.insert(found.begin(), m[i][j+1]); //east
    found.insert(found.begin(), m[i][j-1]); //west

    sort(found);
    //std::cout << "Found: " << found << " at " << i << ' ' << j << std::endl;
    for(int i = found.size(); i > 0; --i)
    {
        if(found[i-1] == found[i])
        return false;
    }

    return true;
}

//=============================================================================
// Compute the first (row, col) position such that this is the center of a
// cross of 5 index positions where the characters in array m at these have
// distinct characters. For instance this is a cross
//  d
// abc
//  e
// of distinct chracters. If the b is at row 5, column 2 then the function
// should set parameter row to 5 and col to 2.
// (Don't forget that we start counting row and column index values at 0.)
//=============================================================================
void f(char m[SIZE][SIZE], int & row, int & col)
{
    for(int i = 1; i < SIZE-1; ++i)
    {
        for(int j = 1; j < SIZE-1; ++j)
        {
            if(checkcross(m, i, j))
            {
                row = i;
                col = j;
                return;
            }
        }
    }
    row = -1;
    col = -1;
}

int main()
{
    int seed;
    std::cin >> seed;
    
    srand(seed);
    char m[SIZE][SIZE];
    
    randarray(m);
    printarray(m);
    
    int row = 0, col = 0;
    f(m, row, col);
    std::cout << row << ' ' << col << std::endl;
    
    return 0;
}
