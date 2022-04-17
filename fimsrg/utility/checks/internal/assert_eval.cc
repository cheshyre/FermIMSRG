// Copyright 2022 Matthias Heinz
#include "fimsrg/utility/checks/internal/assert_eval.h"

#include <stdexcept>

#include "fmt/core.h"
#include "spdlog/spdlog.h"

namespace fimsrg {
namespace internal {

void CheckPrecondition(bool val, const char* file, int line,
                       const char* assertion) {
  if (!val) {
    spdlog::error("Precondition failed ({}:{}): {}", file, line, assertion);
    throw fimsrg::internal::PreconditionError(
        fmt::format("Precondition failed ({}:{}): {}", file, line, assertion));
  }
}

void CheckAssertion(bool val, const char* file, int line,
                    const char* assertion) {
  if (!val) {
    spdlog::error("Assertion failed ({}:{}): {}", file, line, assertion);
    throw fimsrg::internal::AssertionError(
        fmt::format("Assertion failed ({}:{}): {}", file, line, assertion));
  }
}

void CheckPostcondition(bool val, const char* file, int line,
                        const char* assertion) {
  if (!val) {
    spdlog::error("Postcondition failed ({}:{}): {}", file, line, assertion);
    throw fimsrg::internal::PostconditionError(
        fmt::format("Postcondition failed ({}:{}): {}", file, line, assertion));
  }
}

}  // namespace internal
}  // namespace fimsrg
