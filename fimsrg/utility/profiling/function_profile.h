// Copyright 2022 Matthias Heinz
//
// This file provides ProfileFunction() and ProfileFunctionWithSize(x),
// two macros designed to make profiling a function easy.
// Placing one of these calls at the beginning of a function body
// will generate a profiling event for each function call
// with the event name being the function name.
//
// ProfileFunctionWithSize(x) gives the option to provide a size x
// as a parameter. This helps to distinguish different function calls
// of different sizes that have a runtime that should depend on the size.
#ifndef FIMSRG_UTILITY_PROFILING_FUNCTION_PROFILE_H_
#define FIMSRG_UTILITY_PROFILING_FUNCTION_PROFILE_H_

#include "fimsrg/utility/profiling/internal/single_event_profiler.h"

#define ProfileFunction()                                             \
  const auto prof =                                                   \
      fimsrg::internal::SingleEventProfiler::MakeSingleEventProfiler( \
          __func__);                                                  \
  (void)prof;

#define ProfileFunctionWithPrefix(x)                        \
  const auto prof = fimsrg::internal::SingleEventProfiler:: \
      MakeSingleEventProfilerWithPrefix(__func__, x);       \
  (void)prof;

#define ProfileFunctionWithSize(x)                                            \
  const auto prof =                                                           \
      fimsrg::internal::SingleEventProfiler::MakeSingleEventProfilerWithSize( \
          __func__, x);                                                       \
  (void)prof;

#define ProfileFunctionWithPrefixAndSize(x, y)                  \
  const auto prof = fimsrg::internal::SingleEventProfiler::     \
      MakeSingleEventProfilerWithPrefixAndSize(__func__, x, y); \
  (void)prof;

#endif  // FIMSRG_UTILITY_PROFILING_FUNCTION_PROFILE_H_
