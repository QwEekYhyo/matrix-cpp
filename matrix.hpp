#ifndef REEL_BEAST_MATRIX
#define REEL_BEAST_MATRIX

#include <array>
#include <stdexcept>

template <typename T, std::size_t rows, std::size_t columns = rows>
class matrix {
    public:
        struct index {
            std::size_t x, y;
        };

        inline static matrix<T, rows, rows> indentity();

        inline matrix();
        inline matrix(std::array<std::array<T, columns>, rows>);

        inline T& operator[](index i);

        inline T& at(index i);
        inline const T& at(index i) const;

        std::array<std::array<T, columns>, rows> m_buffer{0}; //this will be private
    private:
        void ensure_range(index i) const;
};

template <typename T, std::size_t rows, std::size_t columns>
matrix<T, rows, columns>::matrix() = default;

template <typename T, std::size_t rows, std::size_t columns>
matrix<T, rows, columns>::matrix(std::array<std::array<T, columns>, rows> arr)
    : m_buffer{std::move(arr)} {}

template <typename T, std::size_t rows, std::size_t columns>
T& matrix<T, rows, columns>::operator[](matrix::index i) {
    return m_buffer[i.y][i.x];
}

template <typename T, std::size_t rows, std::size_t columns>
void matrix<T, rows, columns>::ensure_range(matrix::index i) const {
    if (i.x >= columns || i.y >= rows)
        throw std::out_of_range("matrix index out of range");
}

template <typename T, std::size_t rows, std::size_t columns>
T& matrix<T, rows, columns>::at(matrix::index i) {
    ensure_range(i);
    return m_buffer.at(i.y).at(i.x);
}

template <typename T, std::size_t rows, std::size_t columns>
const T& matrix<T, rows, columns>::at(matrix::index i) const {
    ensure_range(i);
    return m_buffer.at(i.y).at(i.x);
}

#endif 
