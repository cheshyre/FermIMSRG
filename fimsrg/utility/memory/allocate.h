// Copyright 2022 Matthias Heinz
#ifndef FIMSRG_UTILITY_MEMORY_ALLOCATE_H_
#define FIMSRG_UTILITY_MEMORY_ALLOCATE_H_

#include <cstdlib>

namespace fimsrg {

namespace internal {
// Get a buffer of num_bytes.
//
// Prefer template function T* Allocate<T>.
void* BareAllocate(std::size_t num_bytes);

// Free a buffer of num_bytes.
//
// Prefer template function Deallocate<T>.
void BareDeallocate(void* ptr, std::size_t num_bytes);

// Get a buffer of num_bytes.
//
// Prefer template function T* PooledAllocate<T>.
void* BarePooledAllocate(std::size_t num_bytes);

// Free a buffer of num_bytes.
//
// Prefer template function PooledDeallocate<T>.
void BarePooledDeallocate(void* ptr, std::size_t num_bytes);
}  // namespace internal

// Allocate a buffer for num_elems elements of type T.
//
// num_elems may be 0, in which case T* will be a null_ptr.
template <typename T>
T* Allocate(std::size_t num_elems) {
  return static_cast<T*>(fimsrg::internal::BareAllocate(num_elems * sizeof(T)));
}

// Free a buffer for num_elems elements of type T.
//
// num_elems may be 0.
template <typename T>
void Deallocate(T* ptr, std::size_t num_elems) {
  fimsrg::internal::BareDeallocate(ptr, num_elems * sizeof(T));
}

// Allocate a buffer for num_elems elements of type T.
//
// num_elems may be 0, in which case T* will be a null_ptr.
template <typename T>
T* PooledAllocate(std::size_t num_elems) {
  return static_cast<T*>(
      fimsrg::internal::BarePooledAllocate(num_elems * sizeof(T)));
}

// Free a buffer for num_elems elements of type T.
//
// num_elems may be 0.
template <typename T>
void PooledDeallocate(T* ptr, std::size_t num_elems) {
  fimsrg::internal::BarePooledDeallocate(ptr, num_elems * sizeof(T));
}

}  // namespace fimsrg

#endif  // FIMSRG_UTILITY_MEMORY_ALLOCATE_H_
