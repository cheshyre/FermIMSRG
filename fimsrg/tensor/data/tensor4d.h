// Copyright 2022 Matthias Heinz
#ifndef FIMSRG_TENSOR_DATA_TENSOR4D_H_
#define FIMSRG_TENSOR_DATA_TENSOR4D_H_

#include <cstddef>
#include <utility>

#include "fimsrg/tensor/data/internal/data_buffer.h"

namespace fimsrg {

// A regular 4-d tensor of double precision values.
class Tensor4D {
 public:
  // Build a new tensor with zeros with the same dimension as reference.
  static Tensor4D ZerosLike(const Tensor4D& other);

  // Default constructor (dim = 0, no matrix elements).
  Tensor4D() noexcept;

  // Constructor with single-axis dimension dim.
  explicit Tensor4D(std::size_t dim);

  // Default copy, move, and dtor

  // Get single-axis dimension of tensor.
  std::size_t Dim() const { return dim_; }

  // Get memory stride of index k.
  //
  // This is for advanced use-cases.
  std::size_t StrideK() const { return stride_k_; }

  // Get matrix element at index (i, j, k, l).
  //
  // Requires:
  // - i < Dim()
  // - j < Dim()
  // - k < Dim()
  // - l < Dim()
  double operator()(std::size_t i, std::size_t j, std::size_t k,
                    std::size_t l) const;

  // Get reference to matrix element at index (i, j, k, l).
  //
  // Requires:
  // - i < Dim()
  // - j < Dim()
  // - k < Dim()
  // - l < Dim()
  double& operator()(std::size_t i, std::size_t j, std::size_t k,
                     std::size_t l);

  // Get pointer to underlying buffer.
  //
  // WARNING: This is an API only to be used for advanced use-cases.
  // Specifically, make sure you understand the stride details
  // (what does stride_i_ do and why don't we just use dim_?)
  // before attempting to access matrix elements through the pointer.
  const double* data() const { return buffer_.data(); }

  // Get pointer to underlying buffer.
  //
  // WARNING: This is an API only to be used for advanced use-cases.
  // Specifically, make sure you understand the stride details
  // (what does stride_i_ do and why don't we just use dim_?)
  // before attempting to access matrix elements through the pointer.
  double* data() { return buffer_.data(); }

  // Check that invariants are fulfilled.
  bool CheckInvariants() const;

  // Add another tensor into current tensor.
  //
  // Requires: other.Dim() == Dim();
  Tensor4D& operator+=(const Tensor4D& other);

  // Subtract another tensor from current tensor.
  //
  // Requires: other.Dim() == Dim();
  Tensor4D& operator-=(const Tensor4D& other);

  // Multiply tensor by overall scalar factor.
  Tensor4D& operator*=(double factor);

  // Divide tensor by overall scalar factor.
  //
  // Requires: factor != 0.0;
  Tensor4D& operator/=(double factor);

  // Compute the Frobenius norm (M_ijkl * M_ijkl in Einstein notation).
  double FrobeniusNorm() const;

  // Compute the total number of tensor elements.
  std::size_t NumberOfElements() const;

  // Swap with other tensor.
  void swap(Tensor4D& other) noexcept {
    using std::swap;
    swap(dim_, other.dim_);
    swap(stride_k_, other.stride_k_);
    swap(buffer_, other.buffer_);
  }

 private:
  // Single-axis dimension
  std::size_t dim_ = 0;
  // Elem stride in i (to ensure alignment)
  // Invariant: stride_k_ >= dim_;
  std::size_t stride_k_ = 0;
  // Buffer for matrix elements
  // Invariant: buffer_.size() >= dim_ * dim_ * dim_ * stride_i_;
  fimsrg::internal::DataBuffer buffer_ =
      fimsrg::internal::DataBuffer(dim_ * dim_ * dim_ * stride_k_);
};

// Swap two tensors.
inline void swap(Tensor4D& a, Tensor4D& b) noexcept { a.swap(b); }

// Add two tensors.
//
// Requires: a.Dim() == b.Dim();
Tensor4D operator+(const Tensor4D& a, const Tensor4D& b);

// Subtract tensor b from a.
//
// Requires: a.Dim() == b.Dim();
Tensor4D operator-(const Tensor4D& a, const Tensor4D& b);

// Multiply a tensor by a scalar factor.
Tensor4D operator*(const Tensor4D& tens, double factor);

// Multiply a tensor by a scalar factor.
inline Tensor4D operator*(double factor, const Tensor4D& tens) {
  return operator*(tens, factor);
}

// Divide a tensor by a scalar factor.
//
// Requires: factor != 0.0;
Tensor4D operator/(const Tensor4D& tens, double factor);

}  // namespace fimsrg

#endif  // FIMSRG_TENSOR_DATA_TENSOR4D_H_
