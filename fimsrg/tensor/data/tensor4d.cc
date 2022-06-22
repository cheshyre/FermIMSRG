// Copyright 2022 Matthias Heinz
#include "fimsrg/tensor/data/tensor4d.h"

#include <cstddef>

#include "fimsrg/tensor/data/internal/data_buffer.h"

// PRIVATE
#include "fimsrg/utility/checks/assert.h"
#include "fimsrg/utility/memory/alignment.h"
#include "fimsrg/utility/profiling/function_profile.h"

namespace fimsrg {

namespace internal {
static std::size_t DetermineStrideK(std::size_t dim);
}

Tensor4D Tensor4D::ZerosLike(const Tensor4D& other) {
  ProfileFunctionWithSize(other.Dim());

  return Tensor4D(other.Dim());
}

Tensor4D::Tensor4D() noexcept {}

Tensor4D::Tensor4D(std::size_t dim)
    : dim_(dim),
      stride_k_(fimsrg::internal::DetermineStrideK(dim_)),
      buffer_(dim_ * dim_ * dim_ * stride_k_) {}

double Tensor4D::operator()(std::size_t i, std::size_t j, std::size_t k,
                            std::size_t l) const {
  Expects(i < Dim());
  Expects(j < Dim());
  Expects(k < Dim());
  Expects(l < Dim());
  return buffer_.at(dim_ * dim_ * stride_k_ * i + dim_ * stride_k_ * j +
                    stride_k_ * k + l);
}

double& Tensor4D::operator()(std::size_t i, std::size_t j, std::size_t k,
                             std::size_t l) {
  Expects(i < Dim());
  Expects(j < Dim());
  Expects(k < Dim());
  Expects(l < Dim());
  return buffer_.at(dim_ * dim_ * stride_k_ * i + dim_ * stride_k_ * j +
                    stride_k_ * k + l);
}

bool Tensor4D::CheckInvariants() const {
  return (stride_k_ >= dim_) &&
         (buffer_.size() >= dim_ * dim_ * dim_ * stride_k_);
}

Tensor4D& Tensor4D::operator+=(const Tensor4D& other) {
  Expects(other.Dim() == Dim());
  ProfileFunctionWithSize(Dim());

  for (std::size_t i = 0; i < dim_; i += 1) {
    for (std::size_t j = 0; j < dim_; j += 1) {
      for (std::size_t k = 0; k < dim_; k += 1) {
        for (std::size_t l = 0; l < dim_; l += 1) {
          (*this)(i, j, k, l) += other(i, j, k, l);
        }
      }
    }
  }
  return *this;
}

Tensor4D& Tensor4D::operator-=(const Tensor4D& other) {
  Expects(other.Dim() == Dim());
  ProfileFunctionWithSize(Dim());

  for (std::size_t i = 0; i < dim_; i += 1) {
    for (std::size_t j = 0; j < dim_; j += 1) {
      for (std::size_t k = 0; k < dim_; k += 1) {
        for (std::size_t l = 0; l < dim_; l += 1) {
          (*this)(i, j, k, l) -= other(i, j, k, l);
        }
      }
    }
  }
  return *this;
}

Tensor4D& Tensor4D::operator*=(const double factor) {
  ProfileFunctionWithSize(Dim());

  for (std::size_t i = 0; i < dim_; i += 1) {
    for (std::size_t j = 0; j < dim_; j += 1) {
      for (std::size_t k = 0; k < dim_; k += 1) {
        for (std::size_t l = 0; l < dim_; l += 1) {
          (*this)(i, j, k, l) *= factor;
        }
      }
    }
  }
  return *this;
}

Tensor4D& Tensor4D::operator/=(const double factor) {
  Expects(factor != 0.0);
  ProfileFunctionWithSize(Dim());

  for (std::size_t i = 0; i < dim_; i += 1) {
    for (std::size_t j = 0; j < dim_; j += 1) {
      for (std::size_t k = 0; k < dim_; k += 1) {
        for (std::size_t l = 0; l < dim_; l += 1) {
          (*this)(i, j, k, l) /= factor;
        }
      }
    }
  }
  return *this;
}

double Tensor4D::FrobeniusNorm() const {
  ProfileFunctionWithSize(Dim());

  double norm = 0.0;
  for (std::size_t i = 0; i < dim_; i += 1) {
    for (std::size_t j = 0; j < dim_; j += 1) {
      for (std::size_t k = 0; k < dim_; k += 1) {
        for (std::size_t l = 0; l < dim_; l += 1) {
          norm += (*this)(i, j, k, l) * (*this)(i, j, k, l);
        }
      }
    }
  }
  return norm;
}

std::size_t Tensor4D::NumberOfElements() const { return dim_ * dim_; }

Tensor4D operator+(const Tensor4D& a, const Tensor4D& b) {
  Expects(a.Dim() == b.Dim());
  ProfileFunctionWithSize(a.Dim());

  Tensor4D c(a);
  c += b;
  return c;
}

Tensor4D operator-(const Tensor4D& a, const Tensor4D& b) {
  Expects(a.Dim() == b.Dim());
  ProfileFunctionWithSize(a.Dim());

  Tensor4D c(a);
  c -= b;
  return c;
}

Tensor4D operator*(const Tensor4D& a, const double factor) {
  Tensor4D c(a);
  ProfileFunctionWithSize(a.Dim());

  c *= factor;
  return c;
}

Tensor4D operator/(const Tensor4D& a, const double factor) {
  Expects(factor != 0.0);
  ProfileFunctionWithSize(a.Dim());

  Tensor4D c(a);
  c /= factor;
  return c;
}

namespace internal {
std::size_t DetermineStrideK(std::size_t dim) {
  return fimsrg::RoundUpToMultipleOfAlignment<double>(dim);
}
}  // namespace internal

}  // namespace fimsrg
