#pragma once

#include <exception>
#include <initializer_list>

#include "linalgebratypes.h"

namespace qlib {
namespace math {
namespace linalgebra {

class QlibInvalidVectorIndexException : public std::exception {};
class QlibInvalidVectorOpException : public std::exception {};

class Vector {
  public:
    Vector(size_t size);
    Vector(size_t size, Scalar value);
    Vector(const Vector& other);
    Vector(std::initializer_list<Scalar> list);
    ~Vector();

    bool operator==(const Vector& other) const;
    bool operator!=(const Vector& other) const;

    Vector& operator=(const Vector& other);
    Vector& operator=(std::initializer_list<Scalar> list);
    Vector  operator-() const;
    Vector  operator+(const Vector& other) const;
    Vector& operator+=(const Vector& other);
    Vector  operator-(const Vector& other) const;
    Vector& operator-=(const Vector& other);

    Scalar& operator()(size_t i);
    const Scalar& operator()(size_t i) const;

    size_t size() const;

  private:
    void allocate();
    void destruct();

    size_t _size;

    Scalar* data;
};

}
}
}
