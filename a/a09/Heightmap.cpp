#include <string>
#include <iomanip>
#include <GL/freeglut.h>
#include <cmath>
#include "Heightmap.h"

float Heightmap::get_value(int row, int col, bool & flag)
{
    if(row >= 0 && row <= maxRow_ && col >= 0 && col <= maxCol_)
    {
        flag = true;
        return heightmap_[row][col];
    }
    flag = false;
    return 9999;
}

void Heightmap::calc_normals()
{
    for(int row = 0; row < maxRow_; row++)
    {   
        vec4f point1(0           , heightmap_[row  ][0], row     * zoffset_);
        vec4f point2(1 * xoffset_, heightmap_[row  ][1], row     * zoffset_);
        vec4f point3(0           , heightmap_[row+1][0], row + 1 * zoffset_);
        vec4f point4(1 * xoffset_, heightmap_[row+1][1], row + 1 * zoffset_);
        
        // Set the points connected to the plains to the same normal vector
        vec4f normalVector1 = (point1 - point3) * (point1 - point2);
        normalVector1 = normalVector1 * (float)sqrt(pow(normalVector1.x(), 2) + pow(normalVector1.y(), 2) + pow(normalVector1.z(), 2));
        
        vec4f normalVector2 = (point2 - point1) * (point2 - point3);
        normalVector2 = normalVector2 * (float)sqrt(pow(normalVector2.x(), 2) + pow(normalVector2.y(), 2) + pow(normalVector2.z(), 2));
        
        vec4f normalVector3 =  (point3 - point4) * (point3 - point2);
        normalVector3 = normalVector3 * (float)sqrt(pow(normalVector3.x(), 2) + pow(normalVector3.y(), 2) + pow(normalVector3.z(), 2));
        
        vec4f normalVector4 =  (point4 - point2) * (point4 - point3);
        normalVector4 = normalVector4 / (float)sqrt(pow(normalVector4.x(), 2) + pow(normalVector4.y(), 2) + pow(normalVector4.z(), 2));
               
        normalmap_[row  ][0] = (normalVector1);
        normalmap_[row  ][1] = (normalVector2);
        normalmap_[row+1][0] = (normalVector3);
        normalmap_[row+1][1] = (normalVector4);

        for(int col = 1; col < maxCol_; col++)
        {   
            point1 = vec4f(col     * xoffset_, heightmap_[row  ][col  ], row     * zoffset_);
            point2 = vec4f(col + 1 * xoffset_, heightmap_[row  ][col+1], row     * zoffset_);
            point3 = vec4f(col     * xoffset_, heightmap_[row+1][col  ], row + 1 * zoffset_);
            point4 = vec4f(col + 1 * xoffset_, heightmap_[row+1][col+1], row + 1 * zoffset_);

            normalVector2 = vec4f(point2 - point1) * (point2 - point3);
            normalVector2 = normalVector2 / (float)sqrt(pow(normalVector2.x(), 2) + pow(normalVector2.y(), 2) + pow(normalVector2.z(), 2));
            normalVector4 = vec4f(point4 - point2) * (point4 - point3);
            normalVector4 = normalVector4 / (float)sqrt(pow(normalVector4.x(), 2) + pow(normalVector4.y(), 2) + pow(normalVector4.z(), 2));
        
            normalmap_[row  ][col+1] = (normalVector2);
            normalmap_[row+1][col+1] = (normalVector4);
        }   
    }
}

void Heightmap::diamond_step(int width, float M)
{
    for(int row = 0; row < maxRow_; row += width)
    {   
        for(int col = 0; col < maxCol_; col += width)
        {   
            float value1 = heightmap_[row][col];
            float value2 = heightmap_[row][col+width];
            float value3 = heightmap_[row+width][col];
            float value4 = heightmap_[row+width][col+width];

            heightmap_[row + width/2][col + width/2] = (value1 + value2 + value3 + value4)/4 + (float)rand() / RAND_MAX * M*2 - M;
        } 
    }
}

void Heightmap::square_step(int width, float M)
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

            float value1 = get_value(row-width,    col, flagN);
            float value2 = get_value(row - offset, col + offset, trash);
            float value3 = get_value(row,          col + width, flagE);
            float value4 = get_value(row + offset, col + offset, trash);
            float value5 = get_value(row + width,  col, flagS);
            float value6 = get_value(row + offset, col - offset, trash);
            float value7 = get_value(row,          col - width, flagW);
            float value8 = get_value(row - offset, col - offset, trash);
            float value9 = get_value(row,          col, trash);

            // North
            if(flagN)
                heightmap_[row - offset][col] = (value1 + value2 + value9 + value8)/4 + (float)rand() / RAND_MAX * M*2 - M;
            else
                heightmap_[row - offset][col] = (value2 + value9 + value8)/3 + (float)rand() / RAND_MAX * M*2 - M;

            // South
            if(flagS)
                heightmap_[row + offset][col] = (value9 + value4 + value5 + value6)/4 + (float)rand() / RAND_MAX * M*2 - M;
            else
                heightmap_[row + offset][col] = (value9 + value4 + value6)/3 + (float)rand() / RAND_MAX * M*2 - M;

            // East
            if(flagE)
                heightmap_[row][col + offset] = (value2 + value3 + value4 + value9)/4 + (float)rand() / RAND_MAX * M*2 - M;
            else
                heightmap_[row][col + offset] = (value2 + value4 + value9)/3 + (float)rand() / RAND_MAX * M*2 - M;

            // West
            if(flagW)
                heightmap_[row][col - offset] = (value8 + value9 + value6 + value7)/4 + (float)rand() / RAND_MAX * M*2 - M;
            else
                heightmap_[row][col - offset] = (value8 + value9 + value6)/3 + (float)rand() / RAND_MAX * M*2 - M;
        }
    }
}

void Heightmap::Diamond_Square(float roughness)
{   
    float M = 0.25 * maxCol_; 

    heightmap_[0][0]                = ((float)rand() / RAND_MAX * M*2) - M;
    heightmap_[0][maxCol_]          = ((float)rand() / RAND_MAX * M*2) - M;
    heightmap_[maxRow_][0]          = ((float)rand() / RAND_MAX * M*2) - M;
    heightmap_[maxRow_][maxCol_]    = ((float)rand() / RAND_MAX * M*2) - M;
    
    for(int w = pow(2, n_); w >= 2; w /= 2)
    {
        diamond_step(w, M);
        square_step(w, M);    
        M = M * pow(2,-roughness);
    }
}  

void    Heightmap::draw_triangle_mesh_wired()
{
    /*
       p0      p2     p4     p6
        +------+------+------+
        |     /|     /|     /|
        |    / |    / |    / |
        |   /  |   /  |   /  |
        |  /   |  /   |  /   |
        | /    | /    | /    |
        |/     |/     |/     |
        +------+------+------+
       p1      p3     p5     p7 p8
       p9     /|     /|     /|
        |    / |    / |    / |
        |   /  |   /  |   /  |
        |  /   |  /   |  /   |
        | /    | /    | /    |
        |/     |/     |/     |
        +------+------+------+
       p10      p9     p10    p11
    */
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glFrontFace(GL_CW);
    glBegin(GL_TRIANGLE_STRIP);
    for(long unsigned int i = 0; i < heightmap_.size()-1; ++i)
    {
        for(long unsigned int j = 0; j < heightmap_[i].size(); ++j)
        {
            glVertex3f(xoffset_ * j, heightmap_[i][j],   zoffset_ * i);
            glVertex3f(xoffset_ * j, heightmap_[i+1][j], zoffset_ * i+1);
        }
            glVertex3f(xoffset_ * heightmap_[i].size()-1, 
                       heightmap_[i+1][heightmap_[i].size()-1], 
                       zoffset_ * i + 1);

            glVertex3f(xoffset_,  
                       heightmap_[i+1][0], 
                       zoffset_ * i + 1);
    }
    glEnd();
}

void    Heightmap::draw_triangle_mesh_solid()
{
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glFrontFace(GL_CW);
    glBegin(GL_TRIANGLE_STRIP);
    for(long unsigned int i = 0; i < heightmap_.size()-1; ++i)
    {
        for(long unsigned int j = 0; j < heightmap_[i].size(); ++j)
        {
            glVertex3f(xoffset_ * j, heightmap_[i][j],   zoffset_ * i);
            glVertex3f(xoffset_ * j, heightmap_[i+1][j], zoffset_ * i+1);
        }
            glVertex3f(xoffset_ * heightmap_[i].size()-1, 
                       heightmap_[i+1][heightmap_[i].size()-1], 
                       zoffset_ * i + 1);

            glVertex3f(xoffset_,  
                       heightmap_[i+1][0], 
                       zoffset_ + i + 1);
    }
    glEnd();
}

void Heightmap::print_normalmap()
{
    for(long unsigned int i = 0; i < normalmap_.size(); ++i)
    {
        std::string dir = "";
        std::cout << "|";
        for(long unsigned int j = 0; j < normalmap_[i].size(); ++j)
        {
            std::cout << dir << std::setw(9) << normalmap_[i][j]; dir = ", ";
        }
        std::cout << "|\n";
    }
    std::cout << '\n';
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
