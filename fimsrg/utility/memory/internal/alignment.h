// Copyright 2022 Matthias Heinz
#ifndef FIMSRG_UTILITY_MEMORY_INTERNAL_ALIGNMENT_H_
#define FIMSRG_UTILITY_MEMORY_INTERNAL_ALIGNMENT_H_

#include <cstdlib>

namespace fimsrg {
namespace internal {

#ifdef __cpp_lib_hardware_interference_size
// The minimum alignment to prevent destructive interference.
using min_alignment = std::hardware_destructive_interference_size;
#else
// The minimum alignment to prevent destructive interference.
constexpr std::size_t min_alignment = 64;
#endif

// Internal method to perform alignment round up.
inline std::size_t PerformAlignmentRoundUp(std::size_t num_bytes) {
  return ((num_bytes + min_alignment - 1) / min_alignment) * min_alignment;
}

}  // namespace internal
}  // namespace fimsrg

#endif  // FIMSRG_UTILITY_MEMORY_INTERNAL_ALIGNMENT_H_
