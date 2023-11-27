#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include <iostream>
#include <vector>
#include <cmath>
#include "Vec4f.h"

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
    Heightmap(int n, float xoffset = 1, float zoffset = 1)
    :n_(n), maxRow_(pow(2, n)), maxCol_(pow(2, n)), xoffset_(xoffset), zoffset_(zoffset)
    {
        std::vector<std::vector<float>> temp(pow(2, n)+1, std::vector<float>(pow(2, n)+1, 0));
        heightmap_ = temp;    
        std::vector<std::vector<vec4f>> tempv(pow(2, n), std::vector<vec4f>(pow(2, n+1)));
        normalmap_ = tempv;
    }

    int         n()        const {return n_;}
    int         width()    const {return maxCol_;}
    int         hight()    const {return maxRow_;}

    float &     xoffset()        {return xoffset_;}
    float       xoffset()  const {return xoffset_;}
    float &     zoffset()        {return zoffset_;}
    float       zoffset()  const {return zoffset_;}
    
    std::vector<std::vector<float>> & heightmap()       {return heightmap_;}
    std::vector<std::vector<float>>   heightmap() const {return heightmap_;}

    float       get_value(int row, int col, bool & flag);
    vec4f       get_normal(int row, int col);

    void        calc_normals();
    
    void        diamond_step(int width, float M);
    void        square_step(int width, float M);
    void        Diamond_Square(float roughtness);

    void        draw_triangle_mesh_wired();
    void        draw_triangle_mesh_solid();

    void        print_normalmap();

    Heightmap resize(int n);


private:
    int     n_;
    int     maxRow_;
    int     maxCol_;
    float  xoffset_;
    float  zoffset_;
    std::vector <std::vector<float>> heightmap_;
    std::vector <std::vector<vec4f>> normalmap_;
};
    std::ostream & operator<<(std::ostream& cout, const Heightmap& heightmap);

#endif
