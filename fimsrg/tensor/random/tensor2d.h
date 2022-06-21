// Copyright 2022 Matthias Heinz
#ifndef FIMSRG_TENSOR_RANDOM_TENSOR2D_H_
#define FIMSRG_TENSOR_RANDOM_TENSOR2D_H_

#include <cstddef>

#include "fimsrg/tensor/data/tensor2d.h"

namespace fimsrg {

// Generate a random Tensor2D of a specific dimension.
Tensor2D GenerateRandomTensor2D(std::size_t dim);

}  // namespace fimsrg

#endif  // FIMSRG_TENSOR_RANDOM_TENSOR2D_H_
