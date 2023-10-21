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
            std::cout << "both r and c are to big\n";
            break;
        case 2:
            std::cout << "c is to big\n";
            break;
        case 3:
            std::cout << "r is to big\n";
            break;

        default:
            break;
        }
    }
private:
    int error_code_; 
};

class SizeError: public std::exception
{
public: 
    SizeError()
    :error_code_(0)
    {}
    SizeError(int error_code)
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
            std::cout << "matrix_x row and col size is larger then matrix_y row and col size\n";
            break;
        case 2:
            std::cout << "matrix_x row and col size is smaller then matrix_y row and col size\n";
            break;
        case 3:
            std::cout << "matrix_x rowsize is larger then matrix_y rowsize\n";
            break;
        case 4:
            std::cout << "matrix_x rowsize is smaller then matrix_y rowsize\n";
            break;
        case 5:
            std::cout << "matrix_x colsize is larger then matrix_y colsize\n";
            break;
        case 6:
            std::cout << "matrix_x colsize is smaller then matrix_y colsize\n";
            break;
        case 7:
            std::cout << "matrix_x rowsize is larger then matrix_y colsize\n";
            break;
        case 8:
            std::cout << "matrix_x rowsize is smaller then matrix_y colsize\n";
            break;
        default:
            break;
        }
    }
private:
    int error_code_; 
};

class NotInvertibleError: public std::exception
{};


template <class T>
class Mat;

template<class T>
std::ostream & operator<< (std::ostream& cout, const Mat<T>& matrix );

template<class T>
std::istream & operator>> (std::ostream& cin, const Mat<T>& matrix );

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

    Mat<T> operator*=(const T & c);
    Mat<T> operator*(const T & c) const;

    Mat<T> adj() const; 
    Mat<T> transpose() const;
    Mat<T> find_minor(int row, int col) const;
    T det() const;
    Mat<T> inverse() const;
    
    void print_minors()const;

    // friend std::istream & operator>>(std::istream& cin, Mat& matrix);
    friend std::ostream & operator<< <T>(std::ostream& cout, const Mat& matrix);

private:
    T *p_ = NULL;        // pointer to an array of type int
    T error_return_ = -1;
    int rowsize_;   // number of rows in the matrix
    int colsize_;   // number of columns in the matrix
};

template <class T, typename U>
Mat<T> operator*(const U & c, const Mat<T> & matrix);

// template<class T>
// std::istream& operator>>(std::istream& cin, Mat<T>& matrix)
// {
//     return cin;
// }

template<class T>
std::ostream& operator<<(std::ostream& cout, const Mat<T>& matrix)
{
    int width_size = 3;
    for(int row = 0; row < matrix.rowsize(); ++row)
    {
        for(int col = 0; col < matrix.colsize(); ++col)
        {
            std::string temp = std::to_string (matrix(row, col));
            temp.erase ( temp.find_last_not_of('0') + 1, std::string::npos );
            temp.erase ( temp.find_last_not_of('.') + 1, std::string::npos );
            // std::cout << temp << std::endl;
            // std::cout << "width_size: " << width_size << std::endl;
            if(temp.size() > width_size)
                width_size = temp.size();
        }
    }

    for(int row = 0; row < matrix.rowsize(); ++row)
    {
        cout << "|";
        for(int col = 0; col < matrix.colsize(); ++col)
        {
            if(col+1 == matrix.colsize())
                cout << std::setw(0) <<std::left << matrix.p_[(row * matrix.colsize()) + col];
            else
                cout << std::setw(width_size) << std::left << matrix.p_[(row * matrix.colsize()) + col];
        }
        cout << "|\n";
    }
    return cout;
}

#endif