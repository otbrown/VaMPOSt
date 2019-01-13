#ifndef VAMPOST_TENSOR_H
#define VAMPOST_TENSOR_H

#include <array>
#include <vector>
#include "datatypes.h"

namespace vampost {
  class SiteTensor {
    private:
      static const int NDIMS = 4;
      const std::array<int,NDIMS> DIMS;
      std::vector<vampost::Complex> data;

      int linearIndex(int, int, int, int);
      int linearIndex(int, int);
      std::vector<vampost::Complex>::iterator getIter(int, int, int, int);
      std::vector<vampost::Complex>::iterator getIter(int, int);

    public:
      SiteTensor(int, int, int);

      size_t getSize() { return data.size(); }
      std::vector<vampost::Complex>::iterator begin() { return data.begin(); }
      std::vector<vampost::Complex>::iterator end() { return data.end(); }

      vampost::Complex getElement(int, int, int, int);
      std::vector<vampost::Complex> getMatrix(int, int);
  };
}

#endif