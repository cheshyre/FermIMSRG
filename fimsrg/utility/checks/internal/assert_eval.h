// Copyright 2022 Matthias Heinz
#ifndef FIMSRG_UTILITY_CHECKS_INTERNAL_ASSERT_EVAL_H_
#define FIMSRG_UTILITY_CHECKS_INTERNAL_ASSERT_EVAL_H_

#include <stdexcept>

namespace fimsrg {
namespace internal {

// Exception class to signal runtime precondition error.
class PreconditionError : public std::logic_error {
  // Inherit constructor
  using std::logic_error::logic_error;
};

// Exception class to signal runtime assertion error.
class AssertionError : public std::logic_error {
  // Inherit constructor
  using std::logic_error::logic_error;
};

// Exception class to signal runtime postcondition error.
class PostconditionError : public std::logic_error {
  // Inherit constructor
  using std::logic_error::logic_error;
};

// Check precondition (val).
//
// If check fails, log error and raise fatal exception.
void CheckPrecondition(bool val, const char* file, int line,
                       const char* assertion);

// Check assertion (val).
//
// If check fails, log error and raise fatal exception.
void CheckAssertion(bool val, const char* file, int line,
                    const char* assertion);

// Check postcondition (val).
//
// If check fails, log error and raise fatal exception.
void CheckPostcondition(bool val, const char* file, int line,
                        const char* assertion);

}  // namespace internal
}  // namespace fimsrg

#endif  // FIMSRG_UTILITY_CHECKS_INTERNAL_ASSERT_EVAL_H_
