// Copyright 2022 Matthias Heinz
#include "fimsrg/utility/memory/alignment.h"

#include <cstdlib>

#include "fimsrg/utility/memory/internal/alignment.h"

namespace fimsrg {
namespace internal {
std::size_t BareRoundUpToMultipleOfAlignment(std::size_t num_bytes) {
  using fimsrg::internal::min_alignment;
  return ((num_bytes + min_alignment - 1) / min_alignment) * min_alignment;
}
}  // namespace internal

std::size_t GetMinimumAlignment() { return fimsrg::internal::min_alignment; }

}  // namespace fimsrg
