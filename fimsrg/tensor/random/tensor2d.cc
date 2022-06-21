// Copyright 2022 Matthias Heinz
#include "fimsrg/tensor/random/tensor2d.h"

#include <cstddef>
#include <random>

#include "fimsrg/tensor/data/tensor2d.h"

namespace fimsrg {

Tensor2D GenerateRandomTensor2D(const std::size_t dim) {
  Tensor2D tens(dim);

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(-10.0, 10.0);

  for (std::size_t i = 0; i < dim; i += 1) {
    for (std::size_t j = 0; j < dim; j += 1) {
      tens(i, j) = dis(gen);
    }
  }

  return tens;
}

}  // namespace fimsrg
