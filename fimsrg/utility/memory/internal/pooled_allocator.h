// Copyright 2022 Matthias Heinz
#ifndef FIMSRG_UTILITY_MEMORY_INTERNAL_POOLED_ALLOCATOR_H_
#define FIMSRG_UTILITY_MEMORY_INTERNAL_POOLED_ALLOCATOR_H_

#include <cstdlib>
#include <vector>

#include "absl/container/flat_hash_map.h"

namespace fimsrg {
namespace internal {

// Singleton to manage a memory pool.
//
// The model is that allocated buffers are reused after free,
// allowing successive allocations to be essentially free while
// incurring a consistent memory usage penalty (the memory usage
// will always be at the maximum concurrent memory usage
// in the program).
class PooledAllocatorSingleton {
 public:
  // Get instance of the pooled allocator singleton.
  static PooledAllocatorSingleton& GetInstance();

  // Singleton cannot be copied.
  PooledAllocatorSingleton(const PooledAllocatorSingleton&) = delete;

  // Singleton cannot be copied.
  void operator=(const PooledAllocatorSingleton&) = delete;

  // Singleton cannot be moved.
  PooledAllocatorSingleton(PooledAllocatorSingleton&&) = delete;

  // Singleton cannot be moved.
  void operator=(PooledAllocatorSingleton&&) = delete;

  // Allocate a buffer of num_bytes.
  void* BareAllocate(std::size_t num_bytes);

  // Free a previously allocated buffer at ptr of num_bytes.
  void BareDeallocate(void* ptr, std::size_t num_bytes);

 private:
  // Default constructor.
  PooledAllocatorSingleton();

  // Destructor.
  ~PooledAllocatorSingleton();

  // memory_pool_[num_bytes] is a vector of pointers to unused num_bytes-sized
  // buffers.
  absl::flat_hash_map<std::size_t, std::vector<void*>> memory_pool_;
  // num_buffers_[num_bytes] is the number of unique num_bytes-sized buffers
  // allocated.
  absl::flat_hash_map<std::size_t, std::size_t> num_buffers_;
};

}  // namespace internal
}  // namespace fimsrg

#endif  // FIMSRG_UTILITY_MEMORY_INTERNAL_POOLED_ALLOCATOR_H_
