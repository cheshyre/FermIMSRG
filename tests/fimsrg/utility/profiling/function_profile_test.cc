// Copyright 2022 Matthias Heinz
#include "fimsrg/utility/profiling/function_profile.h"

#include "catch2/catch.hpp"

#include "fimsrg/utility/profiling/profile_report.h"

static int One() {
  ProfileFunction();
  return 1;
}

static int TimesTen(int val) {
  ProfileFunctionWithSize(val);
  return val * 10;
}

TEST_CASE("Test profiling two functions gives two profile entries.") {
  int val = 0;

  val += One();
  val += TimesTen(100);

  REQUIRE(val == 1001);
  const auto entries = fimsrg::GetProfileReportEntries();
  REQUIRE(entries.size() == 2);
}
