// Copyright 2022 Matthias Heinz
#include "fimsrg/utility/checks/assert.h"

namespace fimsrg {

bool RuntimeChecksEnabled() { return fimsrg::internal::kRuntimeChecksEnabled; }

}  // namespace fimsrg
