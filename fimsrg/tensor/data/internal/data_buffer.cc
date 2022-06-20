// Copyright 2022 Matthias Heinz
#include "fimsrg/tensor/data/internal/data_buffer.h"

#include <cstddef>

#include "fimsrg/utility/memory/allocate.h"

namespace fimsrg {
namespace internal {
DataBuffer::DataBuffer() {}

DataBuffer::DataBuffer(std::size_t num_elems)
    : num_elems_(num_elems),
      data_ptr_(fimsrg::PooledAllocate<double>(num_elems_)) {}

DataBuffer::DataBuffer(const DataBuffer& other) : DataBuffer() {
  // TODO(mheinz): implement
  (void)other;
}

DataBuffer::DataBuffer(DataBuffer&& other) : DataBuffer() {
  // TODO(mheinz): implement
  (void)other;
}

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
  // TODO(mheinz): implement
  (void)index;
  return data_ptr_[0];
}

double& DataBuffer::at(std::size_t index) {
  // TODO(mheinz): implement
  (void)index;
  return data_ptr_[0];
}
}  // namespace internal
}  // namespace fimsrg
