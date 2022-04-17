// Copyright 2022 Matthias Heinz
#ifndef FIMSRG_UTILITY_CHECKS_ERROR_H_
#define FIMSRG_UTILITY_CHECKS_ERROR_H_

#include <string>
#include <string_view>
#include <utility>

#include "fimsrg/utility/checks/internal/error_eval.h"

#define ErrorMessage(x) \
  fimsrg::internal::GenerateFullErrorMessage(__FILE__, __LINE__, x);

namespace fimsrg {

// Return value of a validation function.
//
// This type is useful for a complex validation with many possible failures.
struct ValidationResult {
  bool valid = true;
  std::string err_msg = "";
};

// Swap validation results.
inline void swap(ValidationResult& a, ValidationResult& b) noexcept {
  using std::swap;
  swap(a.valid, b.valid);
  swap(a.err_msg, b.err_msg);
}

// Check for error state.
//
// If in error state (error_state == true),
// the error message will be logged and a fatal exception will be raised.
void CheckForError(bool error_state, std::string_view msg);

// Check for error in validation result.
//
// If it is invalid (validation_result.valid == false),
// the error message will be logged and a fatal exception will be raised.
void CheckForError(const ValidationResult& validation_result);

}  // namespace fimsrg

#endif  // FIMSRG_UTILITY_CHECKS_ERROR_H_
