// Copyright 2022 Matthias Heinz
#include "fimsrg/tensor/data/internal/data_buffer.h"

#include <cstddef>

#include "fimsrg/utility/checks/assert.h"
#include "fimsrg/utility/memory/allocate.h"

namespace fimsrg {
namespace internal {

static double* AllocateAndCopyBuffer(const double* src_buffer_ptr,
                                     std::size_t src_buffer_size);

DataBuffer::DataBuffer() {}

DataBuffer::DataBuffer(std::size_t num_elems)
    : num_elems_(num_elems),
      data_ptr_(fimsrg::PooledAllocate<double>(num_elems_)) {}

DataBuffer::DataBuffer(const DataBuffer& other)
    : num_elems_(other.size()),
      data_ptr_(AllocateAndCopyBuffer(other.data(), other.size())) {}

DataBuffer::DataBuffer(DataBuffer&& other) : DataBuffer() { swap(other); }

DataBuffer::~DataBuffer() { fimsrg::PooledDeallocate(data_ptr_, num_elems_); }

DataBuffer& DataBuffer::operator=(const DataBuffer& other) {
  // TODO(mheinz): implement
  (void)other;

  return *this;
}

DataBuffer& DataBuffer::operator=(DataBuffer&& other) {
  // TODO(mheinz): implement
  (void)other;

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
  double* new_buffer_ptr = fimsrg::PooledAllocate<double>(src_buffer_size);

  for (std::size_t i = 0; i < src_buffer_size; i += 1) {
    new_buffer_ptr[i] = src_buffer_ptr[i];
  }

  return new_buffer_ptr;
}

}  // namespace internal
}  // namespace fimsrg
