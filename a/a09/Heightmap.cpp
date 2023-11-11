#include <string>
#include <iomanip>
#include <cmath>
#include "Heightmap.h"

double Heightmap::get_value(int row, int col, bool & flag)
{
    if(row >= 0 && row <= maxRow_ && col >= 0 && col <= maxCol_)
    {
        flag = true;
        return heightmap_[row][col];
    }
    flag = false;
    return 9999;
}

void Heightmap::diamond_step(int width, double M)
{
    for(int row = 0; row < maxRow_; row += width)
    {   
        for(int col = 0; col < maxCol_; col += width)
        {   
            double value1   = heightmap_[row][col];
            double value2   = heightmap_[row][col+width];
            double value3   = heightmap_[row+width][col];
            double value4   = heightmap_[row+width][col+width];

            heightmap_[row + width/2][col + width/2] = (value1 + value2 + value3 + value4)/4 + (double)rand() / RAND_MAX * M*2 - M;
        } 
    }
}

void Heightmap::square_step(int width, double M)
{
    int offset = width/2;
    for(int row = offset; row < maxRow_-1/width; row += width)
    {
        for(int col = offset; col < maxCol_-1/width; col += width)
        {   
            bool flagN = true;
            bool flagS = true;
            bool flagE = true;
            bool flagW = true;
            bool trash = true;

            double value1 = get_value(row-width,    col, flagN);
            double value2 = get_value(row - offset, col + offset, trash);
            double value3 = get_value(row,          col + width, flagE);
            double value4 = get_value(row + offset, col + offset, trash);
            double value5 = get_value(row + width,  col, flagS);
            double value6 = get_value(row + offset, col - offset, trash);
            double value7 = get_value(row,          col - width, flagW);
            double value8 = get_value(row - offset, col - offset, trash);
            double value9 = get_value(row,          col, trash);

int DEBUG_LEV = DEBUG_OFF;      // 0 = no Debug

<<<<<<< HEAD
double Heightmap::get_value(int row, int col)
{
    if(row >= 0 && row <= maxRow_ && col >= 0 && col <= maxCol_)
    {
        return heightmap_[row][col];
    }
    return 0;
}

void Heightmap::diamond_step(int width, double M)
{
    // std::cout << "diamond_step for w:" << width << '\n';

    for(int row = 0; row < maxRow_; row += width)
    {   
        for(int col = 0; col < maxCol_; col += width)
        {   
            // std::cout << "row: " << row  << " max row: " << maxRow_ << " col: " << col << " max col: " <<  maxCol_ << "\n";
            double value1   = heightmap_[row][col];
            double value2   = heightmap_[row][col+width];
            double value3   = heightmap_[row+width][col];
            double value4   = heightmap_[row+width][col+width];

            heightmap_[row + width/2][col + width/2] = (value1 + value2 + value3 + value4)/4 + (double)rand() / RAND_MAX * M*2 - M;
        } 
    }
}

void Heightmap::square_step(int width, double M)
{
    // std::cout << "square_step for w:" << width << '\n';
    int offset = width/2;
    for(int row = offset; row < maxRow_-1/width; row += width)
    {
        for(int col = offset; col < maxCol_-1/width; col += width)
        {   
            
            double value1 = get_value(row-width,    col);
            double value2 = get_value(row - offset, col + offset);
            double value3 = get_value(row,          col + width);
            double value4 = get_value(row + offset, col + offset);
            double value5 = get_value(row + width,  col);
            double value6 = get_value(row + offset, col - offset);
            double value7 = get_value(row,          col - width);
            double value8 = get_value(row - offset, col - offset);
            double value9 = get_value(row,          col);

            // North
            heightmap_[row - offset][col] = (value1 + value2 + value9 + value8)/4 + (double)rand() / RAND_MAX * M*2 - M;

            // South
            heightmap_[row + offset][col] = (value9 + value4 + value5 + value6)/4 + (double)rand() / RAND_MAX * M*2 - M;

            // East
            heightmap_[row][col + offset] = (value2 + value3 + value4 + value9)/4 + (double)rand() / RAND_MAX * M*2 - M;
            
            // West
            heightmap_[row][col - offset] = (value8 + value9 + value6 + value7)/4 + (double)rand() / RAND_MAX * M*2 - M;
=======

            // North
            if(flagN)
                heightmap_[row - offset][col] = (value1 + value2 + value9 + value8)/4 + (double)rand() / RAND_MAX * M*2 - M;
            else
                heightmap_[row - offset][col] = (value2 + value9 + value8)/3 + (double)rand() / RAND_MAX * M*2 - M;

            // South
            if(flagS)
                heightmap_[row + offset][col] = (value9 + value4 + value5 + value6)/4 + (double)rand() / RAND_MAX * M*2 - M;
            else
                heightmap_[row + offset][col] = (value9 + value4 + value6)/3 + (double)rand() / RAND_MAX * M*2 - M;

            // East
            if(flagE)
                heightmap_[row][col + offset] = (value2 + value3 + value4 + value9)/4 + (double)rand() / RAND_MAX * M*2 - M;
            else
                heightmap_[row][col + offset] = (value2 + value4 + value9)/3 + (double)rand() / RAND_MAX * M*2 - M;

            // West
            if(flagW)
                heightmap_[row][col - offset] = (value8 + value9 + value6 + value7)/4 + (double)rand() / RAND_MAX * M*2 - M;
            else
                heightmap_[row][col - offset] = (value8 + value9 + value6)/3 + (double)rand() / RAND_MAX * M*2 - M;
>>>>>>> 696865407e09bc65502fab20a9a8f811a4d6d3a7
        }
    }
}

void       Heightmap::Diamond_Square(double roughness)
{   
    double M = 0.25 * maxCol_; 
<<<<<<< HEAD
    std::cout << "max row: " << maxRow_ << " max col: " << maxCol_ << std::endl;
    heightmap_[0][0]              = ((double)rand() / RAND_MAX * M*2) - M;
    heightmap_[0][maxCol_]      = ((double)rand() / RAND_MAX * M*2) - M;
    heightmap_[maxRow_][0]      = ((double)rand() / RAND_MAX * M*2) - M;
    heightmap_[maxRow_][maxCol_]    = ((double)rand() / RAND_MAX * M*2) - M;
    
    // std::cout << *this << '\n';

    for(int w = pow(2, n_); w >= 2; w /= 2)
    {
        diamond_step(w, M);
        // std::cout << *this << '\n';
        square_step(w, M);    
        // std::cout << *this << '\n';
=======

    heightmap_[0][0]                = ((double)rand() / RAND_MAX * M*2) - M;
    heightmap_[0][maxCol_]          = ((double)rand() / RAND_MAX * M*2) - M;
    heightmap_[maxRow_][0]          = ((double)rand() / RAND_MAX * M*2) - M;
    heightmap_[maxRow_][maxCol_]    = ((double)rand() / RAND_MAX * M*2) - M;
    
    for(int w = pow(2, n_); w >= 2; w /= 2)
    {
        diamond_step(w, M);
        square_step(w, M);    
>>>>>>> 696865407e09bc65502fab20a9a8f811a4d6d3a7
        M = M * pow(2,-roughness);
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
            cout << dir << std::setw(9) << heightmap.heightmap()[i][j]; dir = ", ";
        }
        cout << "|\n";

    }
    return cout;
}
