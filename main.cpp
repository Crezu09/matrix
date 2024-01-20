#include <iostream>
#include <array>
#include <cstdlib>
#include <cassert>
#define assertm(exp, msg) assert(((void)msg, exp))


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
                result.m_data[r * C + c] = (*this)(r,c);
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

    std::size_t rows() 
    {
        return R;
    }

    std::size_t cols() 
    {
        return C;
    }
    
    // TODO: check if requires possible ? what is requires anyways...
    template <std::size_t ROW, std::size_t COL>
    void setValue(const T value)
    {
        if(ROW >= R || COL >= C)
        {
            throw std::invalid_argument("Dimension mismatch.");
        }

        m_data[ROW * C + COL] = value;
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

        // Copy A to B
        Matrix2D B(A);

        // Assign A to C
        Matrix2D C = A;

        // Matrix addition
        Matrix2D D = A + B;
        const int x = std::rand() % 100;
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