#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include <iostream>
#include <vector>
#include <cmath>


/* morgan code*/
#define DEBUG_OFF 0
#define DEPTH_01 0x00000001         // Top level output
#define DEPTH_02 0x00000002         // One Layer in
#define DEPTH_03 0x00000004         // Two layers in
#define DEPTH_04 0x00000008         // etc etc
#define DEPTH_05 0x00000010         // Very Spammy shows the values of the array
#define DEPTH_06 0x00000020         // Summary
#define DEPTH_07 0x00000040         // Diamond Step Averages
#define DEPTH_08 0x00000080         // Square Step Averages
#define DEPTH_09 0x00000100
#define DEPTH_10 0x00000200
#define DEPTH_11 0x00000400
#define DEPTH_12 0x00000800


// The Following 4 functions are used for bitwise math
#define IS_SET( flag, bit )	            ( ( flag ) &   ( bit ) )
#define SET_BIT( flag, bit )	        ( ( flag ) |=  ( bit ) )
#define REMOVE_BIT( flag, bit )	        ( ( flag ) &= ~( bit ) )
#define TOGGLE_BIT( flag, bit )         ( ( flag ) ^=  ( bit ) )

class Heightmap
{
public:
    Heightmap()
    :n_(0), maxRow_(0), maxCol_(0)
    {}
    Heightmap(int n)
    :n_(n), maxRow_(pow(2, n)), maxCol_(pow(2, n))
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
