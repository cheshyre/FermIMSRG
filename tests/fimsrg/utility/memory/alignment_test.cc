// Copyright 2022 Matthias Heinz
#include "fimsrg/utility/memory/alignment.h"

#include <cstdint>
#include <cstdlib>

#include "catch2/catch.hpp"

TEST_CASE("Test min_alignment is not less than 64 bytes.") {
  const auto min_alignment = fimsrg::GetMinimumAlignment();
  REQUIRE(min_alignment >= 64);
}
