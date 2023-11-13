#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include <iostream>
#include <vector>
#include <cmath>

class Heightmap
{
public:
    Heightmap()
    :n_(0)
    {}
    Heightmap(int n)
    :n_(n)
    {
        std::vector<std::vector<double>> temp(pow(2, n)+1, std::vector<double>(pow(2, n)+1, 0));
        heightmap_ = temp;
    }

    int & n()           {return n_;}
    int   n()     const {return n_;}
    int   width() const {return maxCol_;}
    std::vector<std::vector<double>> & heightmap()       {return heightmap_;}
    std::vector<std::vector<double>>   heightmap() const {return heightmap_;}


    double    get_value(int row, int col, bool & flag);
    void      diamond_step(int width, double M);
    void      square_step(int width, double M);
    void      Diamond_Square(double roughtness);
    Heightmap resize(int n);

private:
    int     n_;
    int     maxRow_;
    int     maxCol_;
    std::vector <std::vector<double>> heightmap_;
};
    std::ostream & operator<<(std::ostream& cout, const Heightmap& heightmap);

#endif
