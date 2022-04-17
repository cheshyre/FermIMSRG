// Copyright 2022 Matthias Heinz
#include "fimsrg/utility/checks/internal/assert_eval.h"

#include <stdexcept>

namespace fimsrg {
namespace internal {

void CheckPrecondition(bool val, const char* file, int line,
                       const char* assertion) {
  (void)val;
  (void)file;
  (void)line;
  (void)assertion;
}

void CheckAssertion(bool val, const char* file, int line,
                    const char* assertion) {
  (void)val;
  (void)file;
  (void)line;
  (void)assertion;
}

void CheckPostcondition(bool val, const char* file, int line,
                        const char* assertion) {
  (void)val;
  (void)file;
  (void)line;
  (void)assertion;
}

}  // namespace internal
}  // namespace fimsrg
