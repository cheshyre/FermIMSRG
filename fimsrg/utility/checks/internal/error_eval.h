// Copyright 2022 Matthias Heinz
#ifndef FIMSRG_UTILITY_CHECKS_INTERNAL_ERROR_EVAL_H_
#define FIMSRG_UTILITY_CHECKS_INTERNAL_ERROR_EVAL_H_

#include <stdexcept>
#include <string>
#include <string_view>

namespace fimsrg {
namespace internal {

// Exception class to signal general runtime error.
class RuntimeError : public std::runtime_error {
  // Inherit constructor
  using std::runtime_error::runtime_error;
};

// Dress error message with file and line number.
std::string GenerateFullErrorMessage(const char* file, int line,
                                     const char* msg);

// Check for error state (error_state).
//
// If in error state, log error and raise fatal exception.
void CheckForError(bool error_state, std::string_view msg);

}  // namespace internal
}  // namespace fimsrg

#endif  // FIMSRG_UTILITY_CHECKS_INTERNAL_ERROR_EVAL_H_
