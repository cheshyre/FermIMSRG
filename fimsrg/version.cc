// Copyright 2022 Matthias Heinz
#include "fimsrg/version.h"

#include <string>

#include "fmt/core.h"

namespace fimsrg {

std::string VersionString() {
  return fmt::format("{}.{}.{}", MajorVersion(), MinorVersion(),
                     PatchVersion());
}

}  // namespace fimsrg
