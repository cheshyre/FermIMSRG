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

Tensor2D& Tensor2D::operator+=(const Tensor2D& other) {
  Expects(other.Dim() == Dim());

  for (std::size_t i = 0; i < dim_; i += 1) {
    for (std::size_t j = 0; j < dim_; j += 1) {
      (*this)(i, j) += other(i, j);
    }
  }
  return *this;
}

Tensor2D& Tensor2D::operator-=(const Tensor2D& other) {
  Expects(other.Dim() == Dim());

  for (std::size_t i = 0; i < dim_; i += 1) {
    for (std::size_t j = 0; j < dim_; j += 1) {
      (*this)(i, j) -= other(i, j);
    }
  }
  return *this;
}

Tensor2D& Tensor2D::operator*=(const double factor) {
  for (std::size_t i = 0; i < dim_; i += 1) {
    for (std::size_t j = 0; j < dim_; j += 1) {
      (*this)(i, j) *= factor;
    }
  }
  return *this;
}

Tensor2D& Tensor2D::operator/=(const double factor) {
  Expects(factor != 0.0);

  for (std::size_t i = 0; i < dim_; i += 1) {
    for (std::size_t j = 0; j < dim_; j += 1) {
      (*this)(i, j) /= factor;
    }
  }
  return *this;
}

double Tensor2D::FrobeniusNorm() const {
  // TODO(mheinz): implement
  return 0.0;
}

std::size_t Tensor2D::NumberOfElements() const {
  // TODO(mheinz): implement
  return 0;
}

Tensor2D operator+(const Tensor2D& a, const Tensor2D& b) {
  Expects(a.Dim() == b.Dim());
  Tensor2D c(a);
  c += b;
  return c;
}

Tensor2D operator-(const Tensor2D& a, const Tensor2D& b) {
  Expects(a.Dim() == b.Dim());
  Tensor2D c(a);
  c -= b;
  return c;
}

Tensor2D operator*(const Tensor2D& a, const double factor) {
  Tensor2D c(a);
  c *= factor;
  return c;
}

Tensor2D operator/(const Tensor2D& a, const double factor) {
  Expects(factor != 0.0);
  Tensor2D c(a);
  c /= factor;
  return c;
}

namespace internal {
std::size_t DetermineStrideI(std::size_t dim) {
  return fimsrg::RoundUpToMultipleOfAlignment<double>(dim);
}
}  // namespace internal

}  // namespace fimsrg
