#include "SiteTensor.h"

inline int
vampost::SiteTensor::linearIndex(int row, int col, int bra, int ket) {
  return ket * DIMS[1] * DIMS[2] * DIMS[3] + bra * DIMS[2] * DIMS[3]
    + row * DIMS[3] + col;
}

inline int vampost::SiteTensor::linearIndex(int bra, int ket) {
  return ket * DIMS[1] * DIMS[2] * DIMS[3] + bra * DIMS[2] * DIMS[3];
}

std::vector<vampost::Complex>::iterator
vampost::SiteTensor::getIter(int row, int col, int bra, int ket) {
  return data.begin() + linearIndex(row, col, bra, ket);
}

std::vector<vampost::Complex>::iterator
vampost::SiteTensor::getIter(int bra, int ket) {
  return data.begin() + linearIndex(bra, ket);
}

vampost::SiteTensor::SiteTensor(int NROWS, int NCOLS, int HILBY)
  : DIMS{HILBY, HILBY, NROWS, NCOLS},
    data(DIMS[0]*DIMS[1]*DIMS[2]*DIMS[3], 0.0 + 0.0i)
    {};

inline vampost::Complex
vampost::SiteTensor::getElement(int row, int col, int bra, int ket) {
  return data[linearIndex(row, col, bra, ket)];
}

std::vector<vampost::Complex>
vampost::SiteTensor::getMatrix(int bra, int ket) {
  const size_t mat_size = DIMS[2] * DIMS[3];
  const std::vector<vampost::Complex>::const_iterator startIter
    = getIter(bra, ket);

  std::vector<vampost::Complex> mat(startIter, startIter+mat_size);

  return mat;
}
