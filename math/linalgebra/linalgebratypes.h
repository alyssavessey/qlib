#pragma once

#include <complex>
#include <utility>
#include <vector>

namespace qlib {
namespace math {
namespace linalgebra {

class Matrix;
class Vector;

typedef std::complex<double> Scalar;
typedef std::pair<Scalar, Vector> EigenPair;

}
}
}
