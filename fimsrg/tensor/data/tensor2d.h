// Copyright 2022 Matthias Heinz
#ifndef FIMSRG_TENSOR_DATA_TENSOR2D_H_
#define FIMSRG_TENSOR_DATA_TENSOR2D_H_

#include <cstddef>
#include <utility>

#include "fimsrg/tensor/data/internal/data_buffer.h"

namespace fimsrg {

// A regular 2-d tensor (a square matrix) of double precision values.
class Tensor2D {
 public:
  // Build a new tensor with zeros with the same dimension as reference.
  //
  // TODO(mheinz): test on random tensors
  static Tensor2D ZerosLike(const Tensor2D& other);

  // Default constructor (dim = 0, no matrix elements).
  Tensor2D() noexcept;

  // Constructor with single-axis dimension dim.
  explicit Tensor2D(std::size_t dim);

  // Default copy, move, and dtor

  // Get single-axis dimension of tensor.
  std::size_t Dim() const { return dim_; }

  // Get memory stride of index i.
  //
  // This is for advanced use-cases.
  std::size_t StrideI() const { return stride_i_; }

  // Get matrix element at index (i, j).
  //
  // Requires:
  // - i < Dim()
  // - j < Dim()
  double operator()(std::size_t i, std::size_t j) const;

  // Get reference to matrix element at index (i, j).
  //
  // Requires:
  // - i < Dim()
  // - j < Dim()
  double& operator()(std::size_t i, std::size_t j);

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

  // TODO(mheinz): implement arithmetic ops

  // Swap with other tensor.
  void swap(Tensor2D& other) noexcept {
    using std::swap;
    swap(dim_, other.dim_);
    swap(stride_i_, other.stride_i_);
    swap(buffer_, other.buffer_);
  }

 private:
  // Single-axis dimension
  std::size_t dim_ = 0;
  // Elem stride in i (to ensure alignment)
  // Invariant: stride_i_ >= dim_;
  std::size_t stride_i_ = 0;
  // Buffer for matrix elements
  // Invariant: buffer_.size() >= dim_ * stride_i_;
  fimsrg::internal::DataBuffer buffer_ =
      fimsrg::internal::DataBuffer(dim_ * stride_i_);
};

// Swap two tensors.
inline void swap(Tensor2D& a, Tensor2D& b) noexcept { a.swap(b); }

// TODO(mheinz): implement arithmetic ops

}  // namespace fimsrg

#endif  // FIMSRG_TENSOR_DATA_TENSOR2D_H_
