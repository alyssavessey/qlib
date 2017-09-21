#include "matrix.h"

using namespace qlib::math::linalgebra;

Matrix::Matrix(size_t size_m, size_t size_n) :
    size_m(size_m),
    size_n(size_n),
    data(nullptr)
{
    allocate();
}

Matrix::Matrix(size_t size_m, size_t size_n, Scalar value) :
    size_m(size_m),
    size_n(size_n),
    data(nullptr)
{
    allocate();
    for (size_t i = 0; i < size_m; ++i) {
        for (size_t j = 0; j < size_n; ++j) {
            data[i][j] = value;
        }
    }
}

Matrix::Matrix(const Matrix& other) :
    size_m(0),
    size_n(0),
    data(nullptr)
{
    *this = other;
}

Matrix::~Matrix() {
    destruct();
}

bool Matrix::operator==(const Matrix& other) const {
    if ((size_m != other.size_m) || (size_n != other.size_n)) {
        return false;
    }

    for (size_t i = 0; i < size_m; ++i) {   
        for (size_t j = 0; j < size_n; ++j) {
            if (data[i][j] != other.data[i][j]) {
                return false;
            }
        }
    }

    return true;
}

bool Matrix::operator!=(const Matrix& other) const {
    return !(*this == other);
}

Matrix& Matrix::operator=(const Matrix& other) {
    if ((size_m != other.size_m) || (size_n != other.size_n)) {
        destruct();
        size_m = other.size_m;
        size_n = other.size_n;
        allocate();
    }

    for (size_t i = 0; i < size_m; ++i) {
        for (size_t j = 0; j < size_m; ++j) {
            data[i][j] = other.data[i][j];
        }
    }

    return *this;
}

Matrix Matrix::operator-() const {
    Matrix ret(*this);

    for (size_t i = 0; i < size_m; ++i) {
        for (size_t j = 0; j < size_n; ++j) {
            ret(i, j) = -data[i][j];
        }
    }

    return ret;
}

Matrix Matrix::operator+(const Matrix& other) const {
    Matrix ret(*this);
    ret += other;
    return ret;
}

Matrix& Matrix::operator+=(const Matrix& other) {
    if ((size_m != other.size_m) || (size_n != other.size_n)) {
        throw new QlibInvalidMatrixOpException();
    }

    for (size_t i = 0; i < size_m; ++i) {
        for (size_t j = 0; j < size_n; ++j) {
            data[i][j] += other.data[i][j];
        }
    }

    return *this;
}

Matrix Matrix::operator-(const Matrix& other) const {
    Matrix ret(*this);
    ret -= other;
    return ret;
}

Matrix& Matrix::operator-=(const Matrix& other) {
    if ((size_m != other.size_m) || (size_n != other.size_n)) {
        throw new QlibInvalidMatrixOpException();
    }

    for (size_t i = 0; i < size_m; ++i) {
        for (size_t j = 0; j < size_n; ++j) {
            data[i][j] -= other.data[i][j];
        }
    }

    return *this;
}

Scalar& Matrix::operator()(size_t i, size_t j) {
    if ((i >= size_m) || (j >= size_n)) {
        throw new QlibInvalidMatrixIndexException();
    }

    return data[i][j];
}

const Scalar& Matrix::operator()(size_t i, size_t j) const {
    if ((i >= size_m) || (j >= size_n)) {
        throw new QlibInvalidMatrixIndexException();
    }

    return data[i][j];
}

size_t Matrix::M_size() const {
    return size_m;
}

size_t Matrix::N_size() const {
    return size_n;
}

void Matrix::allocate() {
    if (data != nullptr) {
        destruct();
    }
    if ((size_m == 0) || (size_n == 0)) {
        throw new QlibInvalidMatrixSizeException();
    }

    data = new Scalar*[size_m];
    for (size_t i = 0; i < size_m; ++i) {
        data[i] = new Scalar[size_n];
    }
}

void Matrix::destruct() {
    if (data != nullptr) {
        for (size_t i = 0; i < size_m; ++i) {
            delete data[i];
            data[i] = nullptr;
        }
        delete data;
        data = nullptr;
    }

    size_m = 0;
    size_n = 0;
}

// STATIC
Matrix Matrix::identity(size_t size) {
    Matrix ret(size, size, 0.0);
    for (size_t i = 0; i < ret.size_m; ++i) {
        ret(i, i) = 1.0;
    }

    return ret;
}
