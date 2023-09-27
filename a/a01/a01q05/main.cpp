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
void fillarray(char m[SIZE][SIZE], int r, int c)
{
    int temp;
    for(int i = 0; i < r; ++i)
    {
        for(int j = 0; j < c; ++j)
        {
            std::cin >> temp;
            m[i][j] = temp;
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
    int columns_ = 0;
    int maxsum_ = 0;
};

subarray findmax(char m[SIZE][SIZE], int r, int c)
{
    subarray max_sub;
    max_sub.maxsum_ = int(m[0][0]);
    //std::cout << max_sum << std::endl;    

    for(int location_y = 0; location_y < r; ++location_y)
    {
        for(int location_x = 0; location_x < c; ++location_x)
        {    
            for(int rowsCounted = r-location_y; rowsCounted > 0; --rowsCounted)
            {
                for(int columnsCounted = c-location_x; columnsCounted > 0; --columnsCounted)
                {
                    int sum = 0;
                    for(int i = 0; i < rowsCounted; ++i)
                    {
                        for(int j = 0; j < columnsCounted; ++j)
                        {
                            sum +=m[location_x + i][location_y + j];
                        }
                        if(sum > max_sub.maxsum_)
                        {
                            max_sub.maxsum_ = sum;
                            max_sub.x_=location_x;
                            max_sub.y_=location_y;
                            max_sub.rows_ = rowsCounted;
                            max_sub.columns_ = columnsCounted;
                        }
                    }
                    // // std::cout << location_x << ' ' 
                    //           << location_y << ' ' 
                    //           << rowsCounted << ' '
                    //           << columnsCounted << ' '
                    //           << "sum: " <<sum << std::endl; 
                }        
            }
        }
    }
    std::cout << "\n\n\n";
    return max_sub;
}

std::ostream & operator<<(std::ostream & cout, const subarray & z)
{
    cout << z.maxsum_ << ' ' << z.x_ << ' ' << z.y_ << ' ' << z.rows_ << ' ' << z.columns_;
    return cout;
}

int main()
{
    int seed;
    int r, c;
    
    //std::cin >> seed; 
    std::cin >> r >> c;
    // srand(seed);
    char m[SIZE][SIZE];
    // randarray(m, r, c);
    fillarray(m, r, c);
    printarray(m, r, c);
    std::cout << '\n' << findmax(m, r, c) << std::endl;
    return 0;
}