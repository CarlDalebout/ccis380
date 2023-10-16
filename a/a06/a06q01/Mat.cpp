#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "Mat.h"

template <class T>
void check_index(const Mat<T> matrix, int r, int c)
{
    if(r >= matrix.rowsize() || c >= matrix.colsize())
    {
        if(r >= matrix.rowsize() && c >= matrix.colsize())
            throw IndexError(1);
        else if(c >= matrix.colsize())
            throw IndexError(2);
        else if(r >= matrix.rowsize())
            throw IndexError(3);
        else
            throw IndexError(0);
    }
}

template <class T>
void check_size(const Mat<T> matrix_x, const Mat<T> matrix_y)
{
    if(matrix_x.rowsize() != matrix_y.rowsize() || matrix_x.colsize() != matrix_y.colsize())
    {
        // matrix_x row and col size is larger then matrix_y row and col size
        if(matrix_x.rowsize() > matrix_y.rowsize() && matrix_x.colsize() > matrix_y.colsize())
            throw IndexError(1);
        
        // matrix_x row and col size is smaller then matrix_y row and col size
        else if(matrix_x.rowsize() < matrix_y.rowsize() && matrix_x.colsize() < matrix_y.colsize())
            throw IndexError(2);
        
        // matrix_x rowsize is larger then matrix_y rowsize
        else if(matrix_x.rowsize() > matrix_y.rowsize())
            throw IndexError(3);
        
        // matrix_x rowsize is smaller then matrix_y rowsize
        else if(matrix_x.rowsize() < matrix_y.rowsize())
            throw IndexError(4);
        
        // matrix_x colsize is larger then matrix_y colsize
        else if(matrix_x.colsize() > matrix_y.colsize())
            throw IndexError(5);
        
        // matrix_x colsize is smaller then matrix_y colsize        
        else if(matrix_x.rowsize() < matrix_y.rowsize())
            throw IndexError(6);
        
        // shit is hitting the fan
        else
            throw IndexError(0);
    }
}

void check_size(const int matrix_x_rowsize_, const int matrix_y_colsize_)
{

    // matrix_x rowsize is larger then matrix_y colsize
    if(matrix_x_rowsize_ > matrix_y_colsize_) 
        throw IndexError(7);
    
    // matrix_x rowsize is smaller then matrix_y colsize
    else if(matrix_x_rowsize_ < matrix_y_colsize_)
        throw IndexError(8);

}

template <class T>
Mat<T> & Mat<T>::operator=(const Mat & matrix)
{
    rowsize_ = matrix.rowsize_;
    colsize_ = matrix.colsize_;
    if(p_ != NULL)
    {
        delete [] p_;
        p_ = NULL;
    }
    p_ = new T[rowsize_ * colsize_];
    // std::cout << p_ << std::endl;
    for(int i = 0; i < (rowsize_ * colsize_); ++i)
    {   
        p_[i] = matrix.p_[i];
    }
    return *this;
}

template <class  T>
bool Mat<T>::operator==(const Mat & matrix)
{
    if(rowsize_ != matrix.rowsize_ || colsize_ != matrix.colsize_)
        return false;
    for(int i = 0; i < (rowsize_ * colsize_); ++i)
    {
        if(p_[i] != matrix.p_[i])
        return false;
    }
    return true;
}

template <class T>
bool Mat<T>::operator!=(const Mat matrix)
{
    return !(*this == matrix);
}

template <class T>
T & Mat<T>::operator()(int r, int c) 
{ 
    check_index(*this, r, c);
    return p_[(r*colsize_) + c]; 
}

template <class T>
const T & Mat<T>::operator()(int r, int c) const 
{ 
    check_index(*this, r, c);
    return p_[(r*colsize_) + c]; 
}

template <typename T>
const Mat<T> & Mat<T>::operator+=(const Mat & matrix)
{
    *this = this->operator+(matrix);
    return *this;
}

template <typename T>
const Mat<T> & Mat<T>::operator-=(const Mat & matrix)
{
    *this = this->operator-(matrix);
    return *this;
}

template <typename T>
const Mat<T> & Mat<T>::operator*=(const Mat & matrix)
{
    *this = this->operator*(matrix);
    return *this;
}

template <typename T>
const Mat<T> & Mat<T>::operator/=(const Mat & matrix)
{
    *this = this->operator/(matrix);
    return *this;
}

template <typename T>
Mat<T> Mat<T>::operator+(Mat const& matrix) const
{
    check_size(*this, matrix);
    Mat<T> ret(rowsize_, colsize_);
    for(int row = 0; row < rowsize_; ++row)
    {
        for(int col = 0; col < colsize_; ++col)
        {
             ret(row, col) = this->operator()(row, col) + matrix(row, col);
        }
    }
    return ret;
}

template <typename T>
Mat<T> Mat<T>::operator-(Mat const& matrix) const
{
    check_size(*this, matrix);
    Mat<T> ret(rowsize_, colsize_);
    for(int row = 0; row < rowsize_; ++row)
    {
        for(int col = 0; col < colsize_; ++col)
        {
             ret(row, col) = this->operator()(row, col) - matrix(row, col);
        }
    }
    return ret;
}

template <typename T>
Mat<T> Mat<T>::operator*(Mat const& matrix) const
{
     check_size(rowsize_, matrix.colsize());
    
    Mat<T> ret(rowsize_, matrix.colsize());
    for (int i = 0; i < rowsize_; i++) {
        for (int j = 0; j < matrix.colsize(); j++) {
            ret(i, j) = 0;
            for (int k = 0; k < matrix.rowsize(); k++) {
                ret(i, j) += this->operator()(i, k) * matrix(k, j);
            }
        }
    }
    return ret;
}

template <typename T>
Mat<T> Mat<T>::operator/(Mat const& matrix) const
{
    Mat<T> ret(rowsize_, matrix.colsize());
    for (int i = 0; i < rowsize_; i++) {
        for (int j = 0; j < matrix.colsize(); j++) {
            ret(i, j) = 0;
            for (int k = 0; k < matrix.rowsize(); k++) {
                ret(i, j) += this->operator()(i, k) / matrix(k, j);
            }
        }
    }
    return ret;
}

template <typename T>
Mat<T> Mat<T>::operator*(const T & c) const
{
    Mat<T> ret(rowsize_, colsize_);
    for(int row = 0; row < rowsize_; ++row)
    {
        for(int col = 0; col < colsize_; ++col)
        {
             ret(row, col) =  c * this->operator()(row, col);
        }
    }
    return ret;
}

template <typename T>
Mat<T> Mat<T>::adj() const
{
    Mat<T> ret(rowsize_, colsize_);
    for(int row = 0; row < rowsize_; ++row)
    {
        for(int col = 0; col < colsize_; ++col)
        {
            if((row + col) % 2 == 0) 
                ret(row, col) = this->find_minor(row, col).det();
            else
                ret(row, col) = -this->find_minor(row, col).det();
        }
    }
    ret = ret.transpose();
    return ret;
}

template <typename T>
Mat<T> Mat<T>::transpose() const
{
    Mat<T> ret(rowsize_, colsize_);
    for(int row = 0; row < rowsize_; ++row)
    {
        for(int col = 0; col < colsize_; ++col)
        {
            ret(row, col) = this->operator()(col, row);
        }
    }
    return ret;
}

template <typename T>
Mat<T> Mat<T>::find_minor(int row_i, int col_j) const
{
    Mat<T> ret( (rowsize_ - 1), (colsize_ - 1) );
    int index = 0;
    for(int row = 0; row < rowsize_; ++row)
    {
        for(int col = 0; col < colsize_; ++col)
        {
            if(row != row_i && col != col_j)
            {
                ret.p_[index] = this->operator()(row, col);
                ++index;
            }
        }
    }
    return ret;
}

template <typename T>
T Mat<T>::det() const
{
    T ret = 0;
    if(rowsize_ == 2 && colsize_ == 2)
    {
        ret = this->operator()(0, 0) * this->operator()(1, 1)
            - this->operator()(0, 1) * this->operator()(1, 0); 
        // std::cout << "\tdet: " << ret << "\n\n";
    }
    else if(rowsize_ == 3 && colsize_ == 3)
    {
        ret = this->operator()(0, 0) * this->operator()(1, 1) * this->operator()(2, 2)
            + this->operator()(0, 1) * this->operator()(1, 2) * this->operator()(2, 0)
            + this->operator()(0, 2) * this->operator()(1, 0) * this->operator()(2, 1)
            - this->operator()(0, 1) * this->operator()(1, 0) * this->operator()(2, 2)
            - this->operator()(0, 0) * this->operator()(1, 2) * this->operator()(2, 1)
            - this->operator()(0, 2) * this->operator()(1, 1) * this->operator()(2, 0);
        // std::cout << "det: " << ret << "\n\n";
    }
    else
    {
        for(int row = 0; row < rowsize_; ++row)
        {
            for(int col = 0; col < colsize_; ++col)
            {
                if((row + col) % 2 == 0)
                {
                    // std::cout << "+(" << row << ", " << col << ") " <<this-> operator()(row, col) << '\n' << this->find_minor(row, col);
                    ret += this->find_minor(row, col).det();
                    // std::cout << "ret = " << ret << "\n";
                }
                else if((row + col) % 2 == 1)
                {
                    // std::cout << "-(" << row << ", " << col << ") " <<this-> operator()(row, col) << '\n' << this->find_minor(row, col);
                    ret += -this->find_minor(row, col).det();
                    // std::cout << "ret = " << ret << "\n";
                }
            }
        }
    }
    return ret;
}

template<typename T>
Mat<T> Mat<T>::inverse() const
{
    T det = 1 / this->det();
    Mat<T> ret(rowsize_, colsize_);
    Mat<T> adj(this->adj());
    for(int row = 0; row < rowsize_; ++row)
    {
        for(int col = 0; col < colsize_; ++col)
        {
            ret(row, col) = det * adj(row, col); 
        }
    }

    return ret;
}

// template <typename T>
// void Mat<T>::print_minors() const
// {
//     std::vector<M<T>> minors;
//     for(int row = 0; row < rowsize_; ++row)
//     {
//         for(int col = 0; col < colsize_; ++col)
//         {
//             minors.push_back(this->find_minor(row, col))
//         }
//     }

//     for(int row = 0; row < rowsize_ - 1; ++row)
//     {
//         for(int col = 0; col < colsize_ - 1; ++col)
//         {
            
//         }
//     }
// }

template class Mat<int>;
template class Mat<float>;
template class Mat<double>;