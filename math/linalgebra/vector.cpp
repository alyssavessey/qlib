#include "vector.h"

using namespace qlib::math::linalgebra;

Vector::Vector(size_t _size) :
    _size(_size)
{
    allocate();
}

Vector::Vector(size_t _size, Scalar value) :
    _size(_size)
{
    allocate();
    for (size_t i = 0; i < _size; ++i) {
        data[i] = value;
    }
}

Vector::Vector(const Vector& other) :
    _size(other._size)
{
    allocate();
    *this = other;
}

Vector::Vector(std::initializer_list<Scalar> list) :
    _size(list.size())
{
    *this = list;
}

Vector::~Vector() {
    destruct();
}

bool Vector::operator==(const Vector& other) const {
    if (_size != other._size) {
        return false;
    }
    for (size_t i = 0; i < _size; ++i) {
        if (data[i] != other.data[i]) {
            return false;
        }
    }
    return true;
}

bool Vector::operator!=(const Vector& other) const {
    return !(*this == other);
}

Vector& Vector::operator=(const Vector& other) {
    if (_size != other._size) {
        _size = other._size;
        allocate();
    }
    for (size_t i = 0; i < _size; ++i) {
        data[i] = other.data[i];
    }
    return *this;
}

Vector& Vector::operator=(std::initializer_list<Scalar> list) {
    if (list.size() != _size) {
        _size = list.size();
        allocate();
    }
    size_t i = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        data[i++] = *it;
    }
    return *this;
}

Vector Vector::operator-() const {
    Vector ret(*this);
    for (size_t i = 0; i < _size; ++i) {
        ret.data[i] = -ret.data[i];
    }
    return ret;
}

Vector Vector::operator+(const Vector& other) const {
    Vector ret(*this);
    ret += other;
    return ret;
}

Vector& Vector::operator+=(const Vector& other) {
    if (_size != other._size) {
        throw new QlibInvalidVectorOpException();
    }
    for (size_t i = 0; i < _size; ++i) {
        data[i] += other.data[i];
    }
    return *this;
}

Vector Vector::operator-(const Vector& other) const {
    Vector ret(*this);
    ret -= other;
    return ret;
}

Vector& Vector::operator-=(const Vector& other) {
    if (_size != other._size) {
        throw new QlibInvalidVectorOpException();
    }
    for (size_t i = 0; i < _size; ++i) {
        data[i] -= other.data[i];
    }
    return *this;
}

Scalar& Vector::operator()(size_t i) {
    if (i >= _size) {
        throw new QlibInvalidVectorIndexException();
    }
    return data[i];
}

const Scalar& Vector::operator()(size_t i) const {
    if (i >= _size) {
        throw new QlibInvalidVectorIndexException();
    }
    return data[i];
}

Scalar Vector::dot(const Vector& other) const {
    if (_size != other._size) {
        throw new QlibInvalidVectorOpException();
    }
    Scalar ret = 0.0;
    for (size_t i = 0; i < _size; ++i) {
        ret += data[i] * other.data[i];
    }
    return ret;
}

size_t Vector::size() const {
    return _size;
}

void Vector::allocate() {
    if (data != nullptr) {
        destruct();
    }
    data = new Scalar[_size];
}

void Vector::destruct() {
    delete[] data;
    data = nullptr;
}
