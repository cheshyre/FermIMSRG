// Copyright 2022 Matthias Heinz
#include "fimsrg/utility/memory/alignment.h"

#include <cstdlib>

#include "fimsrg/utility/memory/internal/alignment.h"

namespace fimsrg {
namespace internal {
std::size_t BareRoundUpToMultipleOfAlignment(std::size_t num_bytes) {
  return PerformAlignmentRoundUp(num_bytes);
}
}  // namespace internal

std::size_t GetMinimumAlignment() { return fimsrg::internal::min_alignment; }

}  // namespace fimsrg
