#include <iostream>
#include <array>

template <typename T, std::size_t R, std::size_t C>
class Matrix2D
{
public:
    Matrix2D() = default;

    Matrix2D(const Matrix2D& m)
    {
        for (std::size_t i = 0; i < R * C; ++i)
        {
            m_data[i] = m.m_data[i];
        }
    }

    Matrix2D(std::initializer_list<T> values)
    {
        if(values.size() != (R * C))
        {
            throw std::invalid_argument("Matrix2D::Matrix2D : Matrix dimension doesn't match with initializer list dimensions.");
        }

        auto it = values.begin();
        for (std::size_t i = 0 ; i < values.size(); ++i) 
        {
            m_data[i] = *(it++);
        }
    }

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

    ~Matrix2D() = default;

    T getValue(std::size_t r, std::size_t c) const
    {
        if(r >= R)
        {
            throw std::invalid_argument("Matrix2D::getValue : Accessing out of bounds row.");
        }

        if(c >= C)
        {
            throw std::invalid_argument("Matrix2D::getValue : Accessing out of bounds column.");
        }
        
        return m_data[r * C + c];
    }

    std::size_t rows() const
    {
        return R;
    }

    std::size_t cols() const
    {
        return C;
    }
    
    Matrix2D operator+ (const Matrix2D& m)
    {
        Matrix2D<T,R,C> result;
        for(std::size_t r = 0 ; r < R ; ++r)
        {
            for(std::size_t c = 0 ; c < C ; ++c)
            {
                result.m_data[r * C + c] = this->getValue(r,c) + m.getValue(r,c);
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
                result.m_data[r * C + c] = this->getValue(r,c) - m.getValue(r,c);
            }
        } 
        
        return result;
    }

    template<std::size_t N>
    Matrix2D<T, R, N> operator*(const Matrix2D<T, C, N>& m) const
    {
        Matrix2D<T,R,N> result;

        // Reihe x Spalte
        for(std::size_t r = 0; r < R; ++r)
        {
            for(std::size_t c = 0; c < C; ++c)
            {
                for(std::size_t x = 0; x < N; ++x)
                {
                    result.setValue()
                }                
            }
        }

        return result; 
    }

private:
    std::array<T, R * C> m_data = {};
};

int main()
{
    try
    {
        // Initialize a matrix with initializer list
        Matrix2D<float, 2, 2> A = 
        {
            1.f, 2.f,
            3.f, 4.f
        };

        std::cout << "Matrix A initialized with following values:\n";
        std::cout << "1, 2\n"
                     "3, 4\n";

        std::cout << "\n";

        // getValue via index
        std::cout << "Value by index A(0,0): " << A.getValue(0,0) << "\n";
        std::cout << "Value by index A(1,1): " << A.getValue(1,1) << "\n";
        std::cout << "\n";

        // Copy Matrix
        Matrix2D B(A);
        std::cout << "A copied into B\n";
        std::cout << "Value by index B(0,0): " << B.getValue(0,0) << "\n";
        std::cout << "Value by index B(1,1): " << B.getValue(1,1) << "\n";
        std::cout << "\n";

        // Assignment
        Matrix2D<float, 2, 2> C;
        C = A;
        std::cout << "A assigned to C\n";
        std::cout << "Value by index C(0,0): " << C.getValue(0,0) << "\n";
        std::cout << "Value by index C(1,1): " << C.getValue(1,1) << "\n";
        std::cout << "\n";

        // + operator
        auto D = A + B;
        std::cout << "D = A + B\n";
        for(std::size_t i = 0 ; i < D.rows() ; ++i)
        {
            for(std::size_t j = 0 ; j < D.cols() ; ++j)
            {
                std::cout << D.getValue(i,j) << ",";
            }
            std::cout << "\n";
        }
        std::cout << "\n";

        // - operator
        auto E = D - B;
        std::cout << "E = D - B\n";
        for(std::size_t i = 0 ; i < E.rows() ; ++i)
        {
            for(std::size_t j = 0 ; j < E.cols() ; ++j)
            {
                std::cout << E.getValue(i,j) << ",";
            }
            std::cout << "\n";
        }
        std::cout << "\n";

        // * operator
        Matrix2D<float,2,2> F = D * B;
        std::cout << "F = D * B\n";
        for(std::size_t i = 0 ; i < F.rows() ; ++i)
        {
            for(std::size_t j = 0 ; j < F.cols() ; ++j)
            {
                std::cout << F.getValue(i,j) << ",";
            }
            std::cout << "\n";
        }

        Matrix2D<float, 2, 3> fMat = {2, 2, 3, 3, 2, 2};
        Matrix2D<float, 3, 2> sMat = {2, 2, 3, 3, 2, 2};

        auto res = fMat * sMat;
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