// Copyright 2022 Matthias Heinz
#include "fimsrg/utility/checks/internal/error_eval.h"

#include <stdexcept>
#include <string>
#include <string_view>

#include "fmt/core.h"
#include "spdlog/spdlog.h"

namespace fimsrg {
namespace internal {

std::string GenerateFullErrorMessage(const char* file, int line,
                                     const char* msg) {
  return fmt::format("({}:{}): {}", file, line, msg);
}

void CheckForError(bool error_state, std::string_view msg) {
  if (error_state) {
    spdlog::error("Runtime error: {}", msg);
    throw fimsrg::internal::RuntimeError(fmt::format("Runtime error: {}", msg));
  }
}

}  // namespace internal
}  // namespace fimsrg
