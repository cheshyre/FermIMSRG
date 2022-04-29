// Copyright 2022 Matthias Heinz
#include "fimsrg/utility/memory/allocate.h"

#include <cstdlib>

// PRIVATE
// fimsrg_memory_internal
#include "fimsrg/utility/memory/internal/basic_allocator.h"
#include "fimsrg/utility/memory/internal/pooled_allocator.h"
// fimsrg::profiling
#include "fimsrg/utility/profiling/function_profile.h"

namespace fimsrg {

namespace internal {
void* BareAllocate(std::size_t num_bytes) {
  ProfileFunctionWithSize(num_bytes);
  return fimsrg::internal::BareAlignedAllocate(num_bytes);
}

void BareDeallocate(void* ptr, std::size_t num_bytes) {
  ProfileFunctionWithSize(num_bytes);
  fimsrg::internal::BareAlignedDeallocate(ptr, num_bytes);
}

void* BarePooledAllocate(std::size_t num_bytes) {
  ProfileFunctionWithSize(num_bytes);
  auto& memory_pool = fimsrg::internal::PooledAllocatorSingleton::GetInstance();
  return memory_pool.BareAlignedAllocate(num_bytes);
}

void BarePooledDeallocate(void* ptr, std::size_t num_bytes) {
  ProfileFunctionWithSize(num_bytes);
  auto& memory_pool = fimsrg::internal::PooledAllocatorSingleton::GetInstance();
  memory_pool.BareAlignedDeallocate(ptr, num_bytes);
}

}  // namespace internal
}  // namespace fimsrg
