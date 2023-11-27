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

vec4f Heightmap::get_normal(int row, int col)
{
    if(col % 2 == 0)
    {
        vec4f point2(row   * zoffset_, heightmap_[row  ][col+1], col+1 * xoffset_); 
        vec4f point3(row+1 * zoffset_, heightmap_[row+1][col  ], col   * xoffset_);
        vec4f point6(row   * zoffset_, heightmap_[row  ][col  ], col  * xoffset_);
        vec4f normalvec = (point6 - point2) * (point6 - point3);
        normalvec = normalvec / sqrt(pow(normalvec.x(), 2) + pow(normalvec.y(), 2) + pow(normalvec.z(), 2));
        return normalvec;
    }
    else
    {
        vec4f point2(row+1 * zoffset_, heightmap_[row+1][col-1], col-1 * xoffset_); 
        vec4f point3(row+1 * zoffset_, heightmap_[row+1][col  ], col   * xoffset_);
        vec4f point6(row   * zoffset_, heightmap_[row  ][col  ], col   * xoffset_);
        vec4f normalvec = (point6 - point3) * (point6 - point2);
        normalvec = (normalvec / sqrt(pow(normalvec.x(), 2) + pow(normalvec.y(), 2) + pow(normalvec.z(), 2)));
        return normalvec;
    }
    // bool flag[] = {false, false, false, false, false, false};

    // vec4f point0;
    // vec4f point1;
    // vec4f point2;
    // vec4f point3;
    // vec4f point4;
    // vec4f point5;

    // //check point up
    // if(row-1 > 0 && col   <= maxCol_)
    //     point0 = vec4f(row-1 * zoffset_, heightmap_[row-1][col  ], col   * xoffset_); flag[0] = true;
    
    // //check point up and right
    // if(row-1 > 0 && col+1 <= maxCol_)
    //     point1 = vec4f(row-1 * zoffset_, heightmap_[row-1][col+1], col+1 * xoffset_); flag[1] = true;

    // //check point right
    // if(col+1 <= maxCol_)
    //     point2 = vec4f(row   * zoffset_, heightmap_[row  ][col+1], col+1 * xoffset_); flag[2] = true;

    // //check point down
    // if(row+1 <= maxRow_)
    //     point3 = vec4f(row+1 * zoffset_, heightmap_[row+1][col  ], col   * xoffset_); flag[3] = true;

    // //check point down and left
    // if(row+1 <= maxRow_ && col-1 > 0)
    //     point4 = vec4f(row+1 * zoffset_, heightmap_[row+1][col-1], col-1 * xoffset_); flag[4] = true;

    // //check point left
    // if(col-1 > 0)
    //     point5 = vec4f(row   * zoffset_, heightmap_[row  ][col-1], col-1 * xoffset_); flag[5] = true;

    // vec4f point6(row   * zoffset_, heightmap_[row  ][col  ], col  * xoffset_); 

    // if(row == 0)
    // {
    //     if(col == 0)
    //     {
    //         vec4f normalvec = (point6 - point3) * (point6 - point2);
    //         normalvec = normalvec / sqrt(pow(normalvec.x(), 2) + pow(normalvec.y(), 2) + pow(normalvec.z(), 2));
    //         return normalvec;
    //     }
    //     else if(col == maxCol_)
    //     {

    //     }
    // }
    return vec4f(0, 1, 0);
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
    glPolygonMode(GL_FRONT, GL_LINE);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glFrontFace(GL_CW);
    glBegin(GL_TRIANGLE_STRIP);
    {
        for(long unsigned int row = 0; row < heightmap_.size()-1; row++)
        {
            glVertex3f(0, heightmap_[row][0], (row * zoffset_));
            glVertex3f(0, heightmap_[row][0], (row * zoffset_));
            for(long unsigned int col = 0; col < heightmap_[row].size()-1; col++)
            {
                glVertex3f(col   * xoffset_, heightmap_[row+1][col  ], row+1 * zoffset_);
                if(col+1 == heightmap_[row].size())
                {
                    glVertex3f(col   * xoffset_, heightmap_[row+1][col  ], row+1 * zoffset_);
                    break;
                }
                glVertex3f(col+1 * xoffset_, heightmap_[row  ][col+1], row  * zoffset_);
            }
            glVertex3f(heightmap_[row].size()-1 * xoffset_, heightmap_[row+1][heightmap_[row].size()-1], row+1 * zoffset_);
            glVertex3f(heightmap_[row].size()-1 * xoffset_, heightmap_[row+1][heightmap_[row].size()-1], row+1 * zoffset_);
        }
    }
    glEnd();
}

void    Heightmap::draw_triangle_mesh_solid()
{
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonMode(GL_FRONT, GL_FILL);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glFrontFace(GL_CW);
    glBegin(GL_TRIANGLE_STRIP);
    {
        for(long unsigned int row = 0; row < heightmap_.size()-1; row++)
        {
            glVertex3f(0, heightmap_[row][0], (row * zoffset_));
            glVertex3f(0, heightmap_[row][0], (row * zoffset_));
            for(long unsigned int col = 0; col < heightmap_[row].size()-1; col++)
            {
                vec4f normv = get_normal(row, col);
                float color = (heightmap_[row+1][col] + 50) / 100;
                glColor3f(0.9f * color, 0.9f * color, 0.9f * color);
                glNormal3f(normv.x(), normv.y(), normv.z());
                glVertex3f(col   * xoffset_, heightmap_[row+1][col  ], row+1 * zoffset_);
                if(col+1 == heightmap_[row].size())
                {
                    glVertex3f(col   * xoffset_, heightmap_[row+1][col  ], row+1 * zoffset_);
                    break;
                }
                glVertex3f(col+1 * xoffset_, heightmap_[row  ][col+1], row  * zoffset_);
            }
            glVertex3f(heightmap_[row].size()-1 * xoffset_, heightmap_[row+1][heightmap_[row].size()-1], row+1 * zoffset_);
            glVertex3f(heightmap_[row].size()-1 * xoffset_, heightmap_[row+1][heightmap_[row].size()-1], row+1 * zoffset_);
        }
    }
    glEnd();
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
