#include <string>
#include <iomanip>
#include <cmath>
#include "Heightmap.h"



void       Heightmap::Diamond_Square()
{   
    int N = pow(2, n_) + 1;
    double M = 0.25 * N; 
    double roughness = 0.5;

    heightmap_[0][0]        = ((double)rand() / RAND_MAX * M*2) - M;
    heightmap_[0][N-1]      = ((double)rand() / RAND_MAX * M*2) - M;
    heightmap_[N-1][0]      = ((double)rand() / RAND_MAX * M*2) - M;
    heightmap_[N-1][N-1]    = ((double)rand() / RAND_MAX * M*2) - M;

    int c = 0;
    for(int w = pow(2, n_); w >= 2; w /= 2)
    {
        int S = pow(2, c);
        double average = 0;
        int row = 0;
        int col = 0;
        std::cout << c << "\n";
        // Diamond Step
        for(int j = 0; j < S; ++j)
        {   
            average = 0;
            if(S != 1 and col == heightmap_.size()-1)
            {
                row += w;
                col  = 0;
            }
            std::cout << "Diamond Step working on square " << j << " of " << S << " Squares | w: " << w << ", col: " << col  << ", row: " << row <<"\n";
            
            average += heightmap_[row][col];
            average += heightmap_[row][col+w];
            average += heightmap_[row+w][col];
            average += heightmap_[row+w][col+w];
            heightmap_[row + w/2][col + w/2] = average/4 + (double)rand() / RAND_MAX * M*2 - M;
            col += w;
        } 
        std::cout << "diamond Step\n" << *this << "\n";
        
        row = 0;
        col = 0;
        // std::cout << "working on square step\n";
        // Square Step
        for(int j = 0; j < S; ++j)
        {
            if(S != 1 and col == heightmap_.size()-1)
            {
                row += w;
                col = 0;
            }
            std::cout << "Square Step working on square " << j+1 << " of " << S << " Squares | w: " << w << ", col: " << col  << ", row: " << row <<"\n";
            {
                std::cout << "working on east ";
                average = 0;
                if(col-w/2 >= 0)
                {
                    std::cout << "left ";
                    average += heightmap_[row+w/2][col-w/2];
                }
                std::cout << "right ";
                average += heightmap_[row+w/2][col+w/2];
                std::cout << "up ";
                average += heightmap_[row][col];
                std::cout << "down ";
                average += heightmap_[row+w][col];
                std::cout << "average\n";
                heightmap_[row+w/2][col] = average/4 + ((double)rand() / RAND_MAX * M*2) - M;
            }
            {
                std::cout << "working on west ";
                average = 0;
                std::cout << "left ";
                average += heightmap_[row+w/2][col+w/2];
                if(col+w/2 <= N)
                {
                    std::cout << "right ";
                    average += heightmap_[row+w/2][col+w/2];
                }
                std::cout << "up ";
                average += heightmap_[row][col+w];
                std::cout << "down ";
                average += heightmap_[row+w][col+w];
                heightmap_[row+w/2][col+w] = average/4 + ((double)rand() / RAND_MAX * M*2) - M;
                std::cout << "average\n";
            }
            {
                std::cout << "working on north ";
                average = 0;
                std::cout << "left ";
                average += heightmap_[row][col];
                std::cout << "right ";
                average += heightmap_[row][col+w];
                if(row-w/2 >= 0)
                {
                    std::cout << "up ";
                    average += heightmap_[row-w/2][col+w/2];
                }
                    std::cout << "down ";
                average += heightmap_[row+w/2][col+w/2];
                heightmap_[row][col+w/2] = average/4 + ((double)rand() / RAND_MAX * M*2) - M;
                std::cout << "average\n";
            }
            {   
                std::cout << "working on south ";
                average = 0;
                std::cout << "left ";
                average += heightmap_[row+w][col];
                std::cout << "right ";
                average += heightmap_[row+w][col+w];
                std::cout << "up ";
                average += heightmap_[row+w/2][col+w/2];
                if((row+w+(w/2)) <= N)
                {
                    std::cout << "down ";
                    average += heightmap_[row+w+(w/2)][col+w/2];
                }
                heightmap_[row+w][col+w/2] = average/4 + ((double)rand() / RAND_MAX * M*2) - M;
                std::cout << "average\n";
            }

            std::cout << *this << '\n';
            col += w;
        }
        
        M = M * pow(2,-roughness);
        c += 2;
    }
}   

Heightmap  Heightmap::resize(int n)
{
    Heightmap temp(n);
    if(n > n_)
    {
        for(long unsigned int i = 0; i < heightmap_.size(); ++i)
            for(long unsigned int j = 0; j < heightmap_[i].size(); ++j)
                temp.heightmap_[i][j] = heightmap_[i][j];
        heightmap_ = temp.heightmap_;
    }
    else
    {
        for(long unsigned int i = 0; i < temp.heightmap_.size(); ++i)
            for(long unsigned int j = 0; j < temp.heightmap_[i].size(); ++j)
                temp.heightmap_[i][j] = heightmap_[i][j];
        heightmap_ = temp.heightmap_;
    }
    return temp;
}

std::ostream & operator<<(std::ostream& cout, const Heightmap& heightmap)
{
    for(long unsigned int i = 0; i < heightmap.heightmap().size(); ++i)
    {
        std::string dir = "";
        cout << "|";
        for(long unsigned int j = 0; j < heightmap.heightmap()[i].size(); ++j)
        {
            cout << dir << std::setw(12) << heightmap.heightmap()[i][j]; dir = ", ";
        }
        cout << "|\n";

    }
    return cout;
}
