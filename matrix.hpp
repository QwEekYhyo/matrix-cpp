#ifndef REEL_BEAST_MATRIX
#define REEL_BEAST_MATRIX

#include <array>

template <typename T, std::size_t rows, std::size_t columns = rows>
class matrix {
    public:
        struct index {
            std::size_t x, y;
        };

        inline static matrix<T, rows, rows> indentity();

        inline matrix();
        inline matrix(std::array<std::array<T, columns>, rows>);

        std::array<std::array<T, columns>, rows> m_buffer{0}; //this will be private
    private:
};

template <typename T, std::size_t rows, std::size_t columns>
matrix<T, rows, columns>::matrix() = default;

template <typename T, std::size_t rows, std::size_t columns>
matrix<T, rows, columns>::matrix(std::array<std::array<T, columns>, rows> arr)
    : m_buffer{std::move(arr)} {}

#endif 
