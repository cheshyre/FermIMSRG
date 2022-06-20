// Copyright 2022 Matthias Heinz
//
// Expects(...), Assert(...), and Ensures(...)
// are macros to evaluate boolean expressions
// that should always be true.
//
// Expects(...) checks for preconditions,
// which should be true at the start of a function call.
//
// Ensures(...) checks for postconditions,
// which should be true at the end of a function call.
//
// Assert(...) checks for general assertions
// that are not easily classified as pre- or postconditions.
//
// Runtime checks are controlled by FIMSRG_RUNTIME_CHECKS_ENABLED,
// which will be set to false for production builds.
#ifndef FIMSRG_UTILITY_CHECKS_ASSERT_H_
#define FIMSRG_UTILITY_CHECKS_ASSERT_H_

#include "fimsrg/utility/checks/internal/assert_eval.h"

#ifndef FIMSRG_RUNTIME_CHECKS_ENABLED
#define FIMSRG_RUNTIME_CHECKS_ENABLED false
#endif

#define Expects(x)                                                  \
  if constexpr (fimsrg::internal::kRuntimeChecksEnabled) {          \
    fimsrg::internal::CheckPrecondition(x, __FILE__, __LINE__, #x); \
  }
#define Assert(x)                                                \
  if constexpr (fimsrg::internal::kRuntimeChecksEnabled) {       \
    fimsrg::internal::CheckAssertion(x, __FILE__, __LINE__, #x); \
  }
#define Ensures(x)                                                   \
  if constexpr (fimsrg::internal::kRuntimeChecksEnabled) {           \
    fimsrg::internal::CheckPostcondition(x, __FILE__, __LINE__, #x); \
  }

namespace fimsrg {
namespace internal {

#if FIMSRG_RUNTIME_CHECKS_ENABLED
constexpr bool kRuntimeChecksEnabled = true;
#else
constexpr bool kRuntimeChecksEnabled = false;
#endif

}  // namespace internal

// Check whether runtime checks are enabled.
bool RuntimeChecksEnabled();

}  // namespace fimsrg

#endif  // FIMSRG_UTILITY_CHECKS_ASSERT_H_
