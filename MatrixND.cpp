
template <typename T, std::size_t... Ds>
class MatrixN
{
public:
    Matrix()
    {

    };

    Matrix(std::initializer_list<T> values)
    {
        if(values.size() != (Ds * ...))
        {
            throw std::invalid_argument("Matrix dimension doesn't match with initializer list dimensions");
        }

        auto it = values.begin();
        for (std::size_t i = 0 ; i < values.size() -1 ; ++i) 
        {
            m_data[i] = *(it++);
        }

        /*
        auto it = values.begin();
        for (std::size_t i = 0 ; i < (Ds * ...); ++i )
        {
            m_data[i] = *(it++);
        }
        */
        
        /*
        auto it = values.begin();
        for (std::size_t i : values) 
        {
            m_data[i] = *(it++);
        }
        */
    }

    ~Matrix() = default;

    template <std::size_t Is>
    T getValue() const
    {

    }

private:
     std::array<T, (Ds * ...)> m_data;
};


