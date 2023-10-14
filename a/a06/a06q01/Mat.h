#ifndef MAT_H
#define MAT_H
#include <iostream>
#include <iomanip>
#include <string>
#include <exception>

class IndexError: public std::exception
{
public: 
    IndexError()
    :error_code_(0)
    {}
    IndexError(int error_code)
    :error_code_(error_code)
    {}

    const int error_code() const { return error_code_;}
    void print_error_code()
    {
        switch (error_code_)
        {
        case 0:
            std::cout << "something is messed up\n";
            break;
        case 1:
            std::cout << "r is to big\n";
            break;
        case 2:
            std::cout << "c is to big\n";
            break;
        case 3:
            std::cout << "both r and c are to big\n";
        
        default:
            break;
        }
    }
private:
    int error_code_; // 0 = unknow error, 1 = r is to large, 2 = c is to large, 3 = both r and c are to large
};

class SizeError: public std::exception
{};

class NotInvertibleError: public std::exception
{};


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
    
    const int rowsize() const { return rowsize_; }
    const int colsize() const { return colsize_; }

    Mat<T> & operator=(const Mat & matrix);

    bool operator==(const Mat & matrix);
    bool operator!=(const Mat matrix);

    T & operator()(int, int);
    const T & operator()(int, int) const;

    const Mat<T> & operator+=(const Mat & matrix);
    const Mat<T> & operator-=(const Mat & matrix);
    const Mat<T> & operator*=(const Mat & matrix);
    const Mat<T> & operator/=(const Mat & matrix);
    
    Mat<T> operator+(Mat const& matrix) const;
    Mat<T> operator-(Mat const& matrix) const;
    Mat<T> operator*(Mat const& matrix) const;
    Mat<T> operator/(Mat const& matrix) const;    
    
private:
    T *p_ = NULL;        // pointer to an array of type int
    T error_return_ = -1;
    int rowsize_;   // number of rows in the matrix
    int colsize_;   // number of columns in the matrix
};

#endif