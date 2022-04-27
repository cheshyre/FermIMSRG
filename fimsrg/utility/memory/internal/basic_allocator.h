// Copyright 2022 Matthias Heinz
#ifndef FIMSRG_UTILITY_MEMORY_INTERNAL_BASIC_ALLOCATOR_H_
#define FIMSRG_UTILITY_MEMORY_INTERNAL_BASIC_ALLOCATOR_H_

#include <cstdlib>
#include <cstring>

#include "fimsrg/utility/memory/internal/alignment.h"

namespace fimsrg {
namespace internal {

// Allocate an aligned buffer of (at least) num_bytes.
//
// Memory is not initialized.
inline void* BareAlignedUninitializedAllocate(std::size_t num_bytes) {
  // Technically align_alloc without the alignment round up is undefined
  // behavior.
  return std::aligned_alloc(fimsrg::internal::min_alignment,
                            PerformAlignmentRoundUp(num_bytes));
}

// Allocate an aligned buffer of num_bytes.
//
// Memory is initialized to 0.
inline void* BareAlignedAllocate(std::size_t num_bytes) {
  void* ptr = fimsrg::internal::BareAlignedUninitializedAllocate(num_bytes);
  std::memset(ptr, 0, num_bytes);
  return ptr;
}

// Free a previously allocated buffer at ptr of num_bytes.
inline void BareAlignedDeallocate(void* ptr, std::size_t num_bytes) {
  (void)num_bytes;
  std::free(ptr);
}

}  // namespace internal
}  // namespace fimsrg

#endif  // FIMSRG_UTILITY_MEMORY_INTERNAL_BASIC_ALLOCATOR_H_
