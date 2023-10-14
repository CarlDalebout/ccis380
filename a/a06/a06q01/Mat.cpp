#include <iostream>
#include "Mat.h"

template <class T>
void check_index(const Mat<T> matrix, int r, int c)
{
    if(r >= matrix.rowsize() || c >= matrix.colsize())
    {
        if(r >= matrix.rowsize() && c >= matrix.colsize())
            throw IndexError(3);
        else if(c >= matrix.colsize())
            throw IndexError(2);
        else if(r >= matrix.rowsize())
            throw IndexError(1);
        else
            throw IndexError(0);
    }
}

template <class T>
void check_size(const Mat<T> matrix_x, const Mat<T> matrix_y)
{
    if(matrix_x.rowsize() != matrix_y.rowsize() || matrix_x.colsize() != matrix_y.colsize())
        throw SizeError();
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

// template <typename T>
// const Mat<T> & Mat<T>::operator+=(const Mat & matrix)
// {
//     try
//     {
//         if(matrix.rowsize_ != rowsize_ || matrix.colsize_ != colsize_)
//             throw SizeError();
//     }
//     catch(SizeError & e)
//     {

//     }
    
//     return *this;
// }

// template <typename T>
// const Mat<T> & Mat<T>::operator-=(const Mat & matrix)
// {

// }

// template <typename T>
// const Mat<T> & Mat<T>::operator*=(const Mat & matrix)
// {

// }

// template <typename T>
// const Mat<T> & Mat<T>::operator/=(const Mat & matrix)
// {

// }

// template <typename T>
// Mat<T> Mat<T>::operator+(Mat const& matrix) const
// {

// }

// template <typename T>
// Mat<T> Mat<T>::operator-(Mat const& matrix) const
// {

// }

// template <typename T>
// Mat<T> Mat<T>::operator*(Mat const& matrix) const
// {

// }

// template <typename T>
// Mat<T> Mat<T>::operator/(Mat const& matrix) const
// {

// } 

template class Mat<int>;
template class Mat<float>;
