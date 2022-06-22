// Copyright 2022 Matthias Heinz
#include "fimsrg/tensor/random/tensor4d.h"

#include <cstddef>
#include <random>

#include "fimsrg/tensor/data/tensor4d.h"

namespace fimsrg {

Tensor4D GenerateRandomTensor4D(const std::size_t dim) {
  Tensor4D tens(dim);

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(-10.0, 10.0);

  for (std::size_t i = 0; i < dim; i += 1) {
    for (std::size_t j = 0; j < dim; j += 1) {
      for (std::size_t k = 0; k < dim; k += 1) {
        for (std::size_t l = 0; l < dim; l += 1) {
          tens(i, j, k, l) = dis(gen);
        }
      }
    }
  }

  return tens;
}

}  // namespace fimsrg
