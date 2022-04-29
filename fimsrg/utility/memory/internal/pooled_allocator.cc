// Copyright 2022 Matthias Heinz
#include "fimsrg/utility/memory/internal/pooled_allocator.h"

#include <cstdlib>
#include <cstring>
#include <vector>

#include "absl/container/flat_hash_map.h"

#include "fimsrg/utility/memory/internal/basic_allocator.h"

// PRIVATE
#include "fimsrg/utility/checks/assert.h"

namespace fimsrg {
namespace internal {

PooledAllocatorSingleton& PooledAllocatorSingleton::GetInstance() {
  static PooledAllocatorSingleton instance;
  return instance;
}

void* PooledAllocatorSingleton::BareAlignedAllocate(std::size_t num_bytes) {
  if (num_bytes == 0) {
    return nullptr;
  }

  std::vector<void*>& buffers = memory_pool_[num_bytes];
  if (buffers.size() == 0) {
    num_buffers_[num_bytes] += 1;
    return fimsrg::internal::BareAlignedAllocate(num_bytes);
  }
  void* ptr = buffers.back();
  buffers.pop_back();
  std::memset(ptr, 0, num_bytes);
  return ptr;
}

void PooledAllocatorSingleton::BareAlignedDeallocate(void* ptr,
                                                     std::size_t num_bytes) {
  if (num_bytes != 0) {
    Expects(memory_pool_[num_bytes].size() < num_buffers_[num_bytes]);
    memory_pool_[num_bytes].push_back(ptr);
  }
}

PooledAllocatorSingleton::PooledAllocatorSingleton() {}

PooledAllocatorSingleton::~PooledAllocatorSingleton() {
  for (const auto& [size, buffers] : memory_pool_) {
    for (const auto& buffer_ptr : buffers) {
      fimsrg::internal::BareAlignedDeallocate(buffer_ptr, size);
    }
  }
}

}  // namespace internal
}  // namespace fimsrg
