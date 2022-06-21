// Copyright 2022 Matthias Heinz
#include "fimsrg/tensor/data/internal/data_buffer.h"

#include <cstddef>

// PRIVATE
#include "fimsrg/utility/checks/assert.h"
#include "fimsrg/utility/memory/allocate.h"
#include "fimsrg/utility/profiling/function_profile.h"

namespace fimsrg {
namespace internal {

static double* AllocateAndCopyBuffer(const double* src_buffer_ptr,
                                     std::size_t src_buffer_size);

DataBuffer::DataBuffer() noexcept {}

DataBuffer::DataBuffer(std::size_t num_elems)
    : num_elems_(num_elems),
      data_ptr_(fimsrg::PooledAllocate<double>(num_elems_)) {}

DataBuffer::DataBuffer(const DataBuffer& other)
    : num_elems_(other.size()),
      data_ptr_(AllocateAndCopyBuffer(other.data(), other.size())) {}

DataBuffer::DataBuffer(DataBuffer&& other) noexcept : DataBuffer() {
  swap(other);
}

DataBuffer::~DataBuffer() { fimsrg::PooledDeallocate(data_ptr_, num_elems_); }

DataBuffer& DataBuffer::operator=(const DataBuffer& other) {
  ProfileFunctionWithSize(other.size());

  // Suboptimal implementation due to reallocation
  // despite perhaps not needing it

  // Free currently allocated memory
  fimsrg::PooledDeallocate(data_ptr_, num_elems_);

  // Copy from other
  num_elems_ = other.size();
  data_ptr_ = AllocateAndCopyBuffer(other.data(), other.size());

  return *this;
}

DataBuffer& DataBuffer::operator=(DataBuffer&& other) noexcept {
  swap(other);

  return *this;
}

double DataBuffer::at(std::size_t index) const {
  Expects(index < size());
  return data_ptr_[index];
}

double& DataBuffer::at(std::size_t index) {
  Expects(index < size());
  return data_ptr_[index];
}

double* AllocateAndCopyBuffer(const double* src_buffer_ptr,
                              std::size_t src_buffer_size) {
  ProfileFunctionWithSize(src_buffer_size);

  double* new_buffer_ptr = fimsrg::PooledAllocate<double>(src_buffer_size);

  for (std::size_t i = 0; i < src_buffer_size; i += 1) {
    new_buffer_ptr[i] = src_buffer_ptr[i];
  }

  return new_buffer_ptr;
}

}  // namespace internal
}  // namespace fimsrg
