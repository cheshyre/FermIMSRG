// Copyright 2022 Matthias Heinz
#include "fimsrg/tensor/data/tensor2d.h"

#include <cstddef>

#include "fimsrg/tensor/data/internal/data_buffer.h"

// PRIVATE
#include "fimsrg/utility/checks/assert.h"
#include "fimsrg/utility/memory/alignment.h"

namespace fimsrg {

namespace internal {
static std::size_t DetermineStrideI(std::size_t dim);
}

Tensor2D Tensor2D::ZerosLike(const Tensor2D& other) {
  return Tensor2D(other.Dim());
}

Tensor2D::Tensor2D() noexcept {}

Tensor2D::Tensor2D(std::size_t dim)
    : dim_(dim),
      stride_i_(fimsrg::internal::DetermineStrideI(dim_)),
      buffer_(dim_ * stride_i_) {}

double Tensor2D::operator()(std::size_t i, std::size_t j) const {
  Expects(i < Dim());
  Expects(j < Dim());
  return buffer_.at(stride_i_ * i + j);
}

double& Tensor2D::operator()(std::size_t i, std::size_t j) {
  Expects(i < Dim());
  Expects(j < Dim());
  return buffer_.at(stride_i_ * i + j);
}

bool Tensor2D::CheckInvariants() const {
  return (stride_i_ >= dim_) && (buffer_.size() >= dim_ * stride_i_);
}

namespace internal {
std::size_t DetermineStrideI(std::size_t dim) {
  return fimsrg::RoundUpToMultipleOfAlignment<double>(dim);
}
}  // namespace internal

}  // namespace fimsrg
