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
        std::vector<std::vector<float>> temp(pow(2, n)+1, std::vector<float>(pow(2, n)+1, 0));
        heightmap_ = temp;
    }

    std::vector<std::vector<float>> & heightmap()       {return heightmap_;}
    std::vector<std::vector<float>>   heightmap() const {return heightmap_;}

    void                              Diamond_Square();
    Heightmap                         resize(int n);

private:
    int     n_;
    std::vector <std::vector<float>> heightmap_;
};
    std::ostream & operator<<(std::ostream& cout, const Heightmap& heightmap);

#endif