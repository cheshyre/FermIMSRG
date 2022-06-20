// Copyright 2022 Matthias Heinz
#ifndef FIMSRG_TENSOR_DATA_INTERNAL_DATA_BUFFER_H_
#define FIMSRG_TENSOR_DATA_INTERNAL_DATA_BUFFER_H_

#include <cstddef>
#include <utility>

namespace fimsrg {
namespace internal {

// Heap-allocated buffer of double-precision numbers.
class DataBuffer {
 public:
  // Default constructor.
  DataBuffer();

  // Construct data buffer with specific number of elements.
  explicit DataBuffer(std::size_t num_elems);

  // Copy constructor.
  DataBuffer(const DataBuffer& other);

  // Move constructor.
  DataBuffer(DataBuffer&& other);

  // Destructor.
  ~DataBuffer();

  // Copy assignment.
  DataBuffer& operator=(const DataBuffer& other);

  // Move assignment.
  DataBuffer& operator=(DataBuffer&& other);

  // Get number of elements.
  //
  // TODO(mheinz): test
  std::size_t size() const { return num_elems_; }

  // Get number at index.
  //
  // Requires: index < size();
  double at(std::size_t index) const;

  // Get mutable reference to number at index.
  //
  // Requires: index < size();
  double& at(std::size_t index);

  // Get pointer to buffer.
  //
  // WARNING: This is an API for advanced applications.
  // Standard bounds-checking and other protections
  // are not available when using the pointer directly.
  // USE WITH CAUTION.
  const double* data() const { return data_ptr_; }

  // Get pointer to buffer.
  //
  // WARNING: This is an API for advanced applications.
  // Standard bounds-checking and other protections
  // are not available when using the pointer directly.
  // USE WITH CAUTION.
  double* data() { return data_ptr_; }

  // Swap with other data buffer.
  void swap(DataBuffer& other) noexcept {
    using std::swap;
    swap(num_elems_, other.num_elems_);
    swap(data_ptr_, other.data_ptr_);
  }

 private:
  // Size of buffer in number of elements
  std::size_t num_elems_ = 0;
  // Pointer to data buffer
  double* data_ptr_ = nullptr;
};

// Swap two data buffers.
inline void swap(DataBuffer& a, DataBuffer& b) noexcept { a.swap(b); }

}  // namespace internal
}  // namespace fimsrg

#endif  // FIMSRG_TENSOR_DATA_INTERNAL_DATA_BUFFER_H_
