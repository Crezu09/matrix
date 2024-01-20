#include <iostream>
#include <array>
#include <cstdlib>
#include <cassert>

template <typename T, std::size_t R, std::size_t C>
class Matrix2D
{
public:
    Matrix2D() = default;

    Matrix2D(std::initializer_list<T> values)
    {
        if(values.size() != (R * C))
        {
            throw std::invalid_argument("Matrix2D::Matrix2D : Dimension mismatch.");
        }

        auto it = values.begin();
        for (std::size_t i = 0 ; i < values.size(); ++i) 
        {
            m_data[i] = *(it++);
        }
    }

    Matrix2D(const Matrix2D& m) 
    {
        for (std::size_t i = 0; i < R * C; ++i)
        {
            m_data[i] = m.m_data[i];
        }
    }

    ~Matrix2D() = default;

    Matrix2D& operator=(const Matrix2D& other)
    {
        if (this != &other)
        {
            for (std::size_t i = 0; i < R * C; ++i)
            {
                m_data[i] = other.m_data[i];
            }
        }
        return *this;
    }

    bool operator== (const Matrix2D& other)
    {
        for(std::size_t r = 0 ; r < R; ++r)
        {
            for(std::size_t c = 0 ; c < C; ++c)
            {
                if ((*this)(r, c) != other(r, c))
                {
                    return false;
                }
            }
        }
        return true;
    }
    
    bool operator!= (const Matrix2D& other)
    {
        return !(*this == other);
    }

    Matrix2D operator+ (const Matrix2D& m)
    {
        Matrix2D<T,R,C> result;
        for(std::size_t r = 0 ; r < R ; ++r)
        {
            for(std::size_t c = 0 ; c < C ; ++c)
            {
                result.m_data[r * C + c] = (*this)(r,c) + m(r,c);
            }
        } 
        return result;
    }

    Matrix2D operator+ (const T value)
    {
        Matrix2D<T,R,C> result;
        for(std::size_t r = 0 ; r < R ; ++r)
        {
            for(std::size_t c = 0 ; c < C ; ++c)
            {
                result.m_data[r * C + c] = (*this)(r,c) + value;
            }
        } 
        return result; 
    }

    Matrix2D operator- (const Matrix2D& m)
    {
        Matrix2D<T,R,C> result;
        for(std::size_t r = 0 ; r < R ; ++r)
        {
            for(std::size_t c = 0 ; c < C ; ++c)
            {
                result.m_data[r * C + c] = (*this)(r,c) - m(r,c);
            }
        } 
        
        return result;
    }

    Matrix2D operator- (const T value)
    {
        Matrix2D<T,R,C> result;
        for(std::size_t r = 0 ; r < R ; ++r)
        {
            for(std::size_t c = 0 ; c < C ; ++c)
            {
                result.m_data[r * C + c] = (*this)(r,c) - value;
            }
        } 
        return result; 
    }

    template<std::size_t N>
    Matrix2D<T, R, N> operator* (const Matrix2D<T, C, N>& m)
    {
        Matrix2D<T,R,N> result;

        // Reihe x Spalte
        for(std::size_t r = 0; r < R; ++r)
        {
            for(std::size_t c = 0; c < C; ++c)
            {
                for(std::size_t x = 0; x < N; ++x)
                {
                    this(r,c)+=this(r,x)*m(x,c);
                }                
            }
        }
        return result; 
    }

    T &operator()(std::size_t r, std::size_t c)
    {
        if (r >= R || c >= C)
        {
            throw std::invalid_argument("Matrix2D::operator[] : Dimension mismatch.");
        }

        return m_data[r * C + c];
    }

    const T &operator()(std::size_t r, std::size_t c) const
    {
        if (r >= R || c >= C)
        {
            throw std::invalid_argument("Matrix2D::operator[] : Dimension mismatch.");
        }

        return m_data[r * C + c];
    }

    friend
    std::ostream& operator<< (std::ostream& os, const Matrix2D& m)
    {
        for(std::size_t r = 0; r < R; ++r)
        {
            for(std::size_t c = 0; c < C; ++c)
            {
                os << m(r,c) << ",";
            }
            os << "\n";
        }
        os << "\n";
        return os;
    }

    std::size_t rows() 
    {
        return R;
    }

    std::size_t cols() 
    {
        return C;
    }

private:
    std::array<T, R * C> m_data = {};
};

int main()
{
    try
    {
        // Define a set of random numbers
        const int value1 = std::rand() % 100;
        const int value2 = std::rand() % 100;
        const int value3 = std::rand() % 100;
        const int value4 = std::rand() % 100;

        // Initialize a matrix with these numbers
        Matrix2D<int, 2, 2> A = {
            value1, value2, value3 ,value4
        };

        Matrix2D<int, 2, 2> AA = {
            value1, value2, value3 ,value4
        };
        
        // Check if operator== working
        if(!(A == AA))
        {
            throw std::logic_error("Main : operator== unexpected result!");
        }

        // Check if operator!= working
        if(A != AA)
        {
            throw std::logic_error("Main : operator!= unexpected result!");
        }

        // Copy A to B
        Matrix2D B(A);
        if(A != B)
        {
            throw(std::logic_error("Main : Copy unexpected result!"));
        }

        // Assign A to C
        Matrix2D C = A;
        if(A != B)
        {
            throw(std::logic_error("Main : Assign unexpected result!"));
        }

        // Matrix addition scalar
        const int x = std::rand() % 100;
        Matrix2D<int,2,2> expected =
        {
            A(0,0) + x, A(0,1) + x,
            A(1,0) + x, A(1,1) + x   
        };
        B = A + x;

        if(B != expected)
        {
            throw(std::logic_error("Main : Addition scalar unexpected result!"));
        }
        
        // Matrix addition
        B = A + A;
        expected(0,0) = 2 * A(0,0);
        expected(0,1) = 2 * A(0,1);
        expected(1,0) = 2 * A(1,0);
        expected(1,1) = 2 * A(1,1);

        if(B != expected)
        {
            throw(std::logic_error("Main : Addition scalar unexpected result!"));
        }

        // Matrix subtract scalar
        B = A - x;
        expected(0,0) = A(0,0) - x;
        expected(0,1) = A(0,1) - x;
        expected(1,0) = A(1,0) - x;
        expected(1,1) = A(1,1) - x;
        if(B != expected)
        {
            throw(std::logic_error("Main : Addition scalar unexpected result!"));
        }
        
        // Matrix subtract
        B = A - A;
        expected(0,0) = 0;
        expected(0,1) = 0;
        expected(1,0) = 0;
        expected(1,1) = 0;

        if(B != expected)
        {
            throw(std::logic_error("Main : Addition scalar unexpected result!"));
        }

        // operator <<
        std::cout << B;
        std::cout << expected;

    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception occured: " << e.what() << "\n";
        return -1;
    }
    catch(...)
    {
        std::cerr << "Unknown exception occured!\n";
        return -1;
    }

    std::cout << "*\nSuccess!\n";
    return 0;
}