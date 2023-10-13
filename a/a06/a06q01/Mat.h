#ifndef MAT_H
#define MAT_H
#include <iostream>

template <typename T>
class Mat
{
public:
    Mat(int rowsize, int colsize, T * p=NULL)
    :rowsize_(rowsize), colsize_(colsize), p_(new T[rowsize * colsize])
    {
            // std::cout << p_ << std::endl;
        if(p != NULL)
        {
            for(int i = 0; i < (rowsize * colsize); ++i)
            {
                p_[i] = p[i];
                // std::cout << "copying " << p[i] << " to p_ index " << i << std::endl; 
            }
        }
    }
    Mat(const Mat & matrix)
    :rowsize_(matrix.rowsize_), colsize_(matrix.colsize_)
    {
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
    }

    Mat<T> & operator=(const Mat & matrix)
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

    ~Mat()
    {
        if(p_ != NULL)
        {
            // std::cout << p_ << std::endl;
            rowsize_ = 0;
            colsize_ = 0;
            // std::cout << "deleting p_" << std::endl;
            delete [] p_;
            p_ = NULL;
        }
    }
    

    bool operator==(const Mat & matrix)
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
    bool operator!=(const Mat matrix)
    {
        return !(*this == matrix);
    }
    
    T & operator()(int r, int c) { return p_[(r*colsize_) + c]; }
    const T & operator()(int r, int c) const { return p_[(r*colsize_) + c]; }
    int rowsize() const { return rowsize_; }
    int colsize() const { return colsize_; }
    T*    p() const { return p_; }
private:
    T *p_ = NULL;        // pointer to an array of type int
    int rowsize_;   // number of rows in the matrix
    int colsize_;   // number of columns in the matrix
};



#endif