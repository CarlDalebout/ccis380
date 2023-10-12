#include <iostream>

class Matrix
{
public:
    Matrix(int rows = 0, int columns = 0)
    :rows_(rows), columns_(columns_)
    {}
    void swap(int row1, int row2);
    void scale_row(int row, float scale);
    void add_matrix(Matrix x);
    void mult_matrix(Matrix x);
    Matrix find_inverse(); 
private:
    int rows_;
    int columns_;
};