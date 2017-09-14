#pragma once

#include <exception>

#include "linalgebratypes.h"

namespace qlib {
namespace math {
namespace linalgebra {

class QlibInvalidMatrixIndexException : public std::exception {};
class QlibInvalidMatrixSizeException : public std::exception {};
class QlibInvalidMatrixOpException : public std::exception{};

class Matrix {
  public:
    Matrix(size_t size_m, size_t size_n);
    Matrix(size_t size_m, size_t size_n, Scalar value);
    Matrix(const Matrix& other);
    ~Matrix();

    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;

    Matrix& operator=(const Matrix& other);
    Matrix  operator-() const;
    Matrix  operator+(const Matrix& other) const;
    Matrix& operator+=(const Matrix& other);
    Matrix  operator-(const Matrix& other) const;
    Matrix& operator-=(const Matrix& other);

    Scalar& operator()(size_t i, size_t j);
    const Scalar& operator()(size_t i, size_t j) const;

    size_t M_size() const;
    size_t N_size() const;

  private:
    void allocate();
    void destruct();

    size_t size_m;
    size_t size_n;

    Scalar** data; // [m][n]

  public:
    static Matrix identity(size_t size);
};

}
}
}
