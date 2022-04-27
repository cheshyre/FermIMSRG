// Copyright 2022 Matthias Heinz
#ifndef FIMSRG_UTILITY_MEMORY_ALIGNMENT_H_
#define FIMSRG_UTILITY_MEMORY_ALIGNMENT_H_

#include <cstdlib>

namespace fimsrg {
namespace internal {

// Rounds up a number of bytes to be a multiple of alignment.
//
// Prefer calling RoundUpToMultipleOfAlignment<T>(num_elems).
std::size_t BareRoundUpToMultipleOfAlignment(std::size_t num_bytes);

}  // namespace internal

// Rounds up a number of elements of type T to correspond
// to a multiple of alignment in memory.
//
// NOTE THAT THIS IS A NUMBER OF ELEMENTS, NOT A NUMBER OF BYTES.
template <typename T>
std::size_t RoundUpToMultipleOfAlignment(std::size_t num_elems) {
  return fimsrg::internal::BareRoundUpToMultipleOfAlignment(num_elems *
                                                            sizeof(T)) /
         sizeof(T);
}

// Get the minimum alignment on the current platform.
//
// This should mostly be used for testing.
std::size_t GetMinimumAlignment();

}  // namespace fimsrg

#endif  // FIMSRG_UTILITY_MEMORY_ALIGNMENT_H_
