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

        inline matrix();
        inline matrix(const matrix<T, rows, columns>&);
        inline matrix(matrix<T, rows, columns>&&);
        inline matrix(std::array<std::array<T, columns>, rows>);

        inline matrix<T, rows, columns>& operator=(const matrix<T, rows, columns>&);
        inline matrix<T, rows, columns>& operator=(matrix<T, rows, columns>&&);

        inline T& operator[](index i);

        inline T& at(index i);
        inline const T& at(index i) const;

        inline const std::array<std::array<T, columns>, rows>& get_buffer() const;

        inline matrix<T, rows, columns> operator-() const;
        inline matrix<T, rows, columns> operator+(const matrix<T, rows, columns>& other) const;
        inline matrix<T, rows, columns> operator-(const matrix<T, rows, columns>& other) const;
        inline matrix<T, rows, columns> operator*(const T& scalar) const;
        template <std::size_t p>
        inline matrix<T, rows, p> operator*(const matrix<T, columns, p>& other) const;
        bool operator==(const matrix<T, rows, columns>&) const;
        bool operator!=(const matrix<T, rows, columns>&) const;

    private:
        std::array<std::array<T, columns>, rows> m_buffer{0};
                                                              
        void ensure_range(index i) const;
};

template <typename T, std::size_t rows, std::size_t columns>
matrix<T, rows, columns>::matrix() = default;

template <typename T, std::size_t rows, std::size_t columns>
matrix<T, rows, columns>::matrix(const matrix<T, rows, columns>& other)
    : m_buffer(other.m_buffer) {}

template <typename T, std::size_t rows, std::size_t columns>
matrix<T, rows, columns>::matrix(matrix<T, rows, columns>&& other)
    : m_buffer(std::move(other.m_buffer)) {}

template <typename T, std::size_t rows, std::size_t columns>
matrix<T, rows, columns>::matrix(std::array<std::array<T, columns>, rows> arr)
    : m_buffer(std::move(arr)) {}

template <typename T, std::size_t rows, std::size_t columns>
matrix<T, rows, columns>& matrix<T, rows, columns>::operator=(const matrix<T, rows, columns>& other) {
    m_buffer = other.m_buffer;
    return *this;
}

template <typename T, std::size_t rows, std::size_t columns>
matrix<T, rows, columns>& matrix<T, rows, columns>::operator=(matrix<T, rows, columns>&& other) {
    m_buffer = other.m_buffer;
    return *this;
}

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

template <typename T, std::size_t rows, std::size_t columns>
const std::array<std::array<T, columns>, rows>& matrix<T, rows, columns>::get_buffer() const {
    return m_buffer;
}

template <typename T, std::size_t rows, std::size_t columns>
matrix<T, rows, columns> matrix<T, rows, columns>::operator+(const matrix<T, rows, columns>& other) const {
    matrix<T, rows, columns> copied = *this;

    for (std::size_t i = 0; i < columns; i++) {
        for (std::size_t j = 0; j < rows; j++) {
            copied.at({i, j}) += other.at({i, j});
        }
    }
    return copied;
}

template <typename T, std::size_t rows, std::size_t columns>
matrix<T, rows, columns> matrix<T, rows, columns>::operator*(const T& scalar) const {
    matrix<T, rows, columns> copied = *this;

    for (std::size_t i = 0; i < columns; i++) {
        for (std::size_t j = 0; j < rows; j++) {
            copied.at({i, j}) *= scalar;
        }
    }
    return copied;
}

template <typename T, std::size_t rows, std::size_t columns>
template <std::size_t p>
matrix<T, rows, p> matrix<T, rows, columns>::operator*(const matrix<T, columns, p>& other) const {
    matrix<T, rows, p> result;

    for (std::size_t i = 0; i < p; i++) {
        for (std::size_t j = 0; j < rows; j++) {
            for (std::size_t k = 0; k < columns; k++) {
                result.at({i, j}) += other.at({i, k}) * at({k, j});
            }
        }
    }
    return result;
}

template <typename T, std::size_t rows, std::size_t columns>
matrix<T, rows, columns> matrix<T, rows, columns>::operator-() const {
    return *this * -1;
}

template <typename T, std::size_t rows, std::size_t columns>
matrix<T, rows, columns> matrix<T, rows, columns>::operator-(const matrix<T, rows, columns>& other) const {
    return *this + -other;
}

template <typename T, std::size_t rows, std::size_t columns>
bool matrix<T, rows, columns>::operator==(const matrix<T, rows, columns>& other) const {
    for (std::size_t i = 0; i < columns; i++) {
        for (std::size_t j = 0; j < rows; j++) {
            if (at({i, j}) != other.at({i, j})) {
                return false;
            }
        }
    }
    return true;
}

template <typename T, std::size_t rows, std::size_t columns>
bool matrix<T, rows, columns>::operator!=(const matrix<T, rows, columns>& other) const {
    return ! (*this == other);
}

#endif 
