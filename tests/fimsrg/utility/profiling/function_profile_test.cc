// Copyright 2022 Matthias Heinz
#include "fimsrg/utility/profiling/function_profile.h"

#include <string>
#include <vector>

#include "fimsrg/utility/profiling/profile_report.h"

#include "catch2/catch.hpp"

static int One() {
  ProfileFunction();
  return 1;
}

static int TimesTen(int val) {
  ProfileFunctionWithSize(val);
  return val * 10;
}

static int Four() {
  ProfileFunctionWithPrefix("four");
  return 4;
}

static int TimesOneHundred(int val) {
  ProfileFunctionWithPrefixAndSize("100x", val);
  return val * 100;
}

TEST_CASE("Test profiling two functions gives two profile entries.") {
  int val = 0;

  val += One();
  val += TimesTen(100);
  val += Four();
  val += TimesOneHundred(1);

  REQUIRE(val == 1105);
  const std::vector<std::string> entries = fimsrg::GetProfileReportEntries();
  REQUIRE(entries.size() == 4);
}
