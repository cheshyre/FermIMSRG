// Copyright 2022 Matthias Heinz
#include "fimsrg/utility/memory/internal/pooled_allocator.h"

#include <cstdlib>
#include <vector>

#include "absl/container/flat_hash_map.h"

#include "fimsrg/utility/memory/internal/basic_allocator.h"

namespace fimsrg {
namespace internal {

PooledAllocatorSingleton& PooledAllocatorSingleton::GetInstance() {
  static PooledAllocatorSingleton instance;
  return instance;
}

void* PooledAllocatorSingleton::BareAllocate(std::size_t num_bytes) {
  return fimsrg::internal::BareAllocate(num_bytes);
}

void PooledAllocatorSingleton::BareDeallocate(void* ptr,
                                              std::size_t num_bytes) {
  return fimsrg::internal::BareDeallocate(ptr, num_bytes);
}

PooledAllocatorSingleton::PooledAllocatorSingleton() {}

PooledAllocatorSingleton::~PooledAllocatorSingleton() {
  for (const auto& [size, buffers] : memory_pool_) {
    for (const auto& buffer_ptr : buffers) {
      fimsrg::internal::BareDeallocate(buffer_ptr, size);
    }
  }
}

}  // namespace internal
}  // namespace fimsrg
