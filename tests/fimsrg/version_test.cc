// Copyright 2022 Matthias Heinz
#include "fimsrg/version.h"

#include <string>
#include <vector>

#include "absl/strings/str_split.h"

#include "catch2/catch.hpp"

#ifndef FIMSRG_MAJOR_VERSION
#define FIMSRG_MAJOR_VERSION -1
#endif

#ifndef FIMSRG_MINOR_VERSION
#define FIMSRG_MINOR_VERSION -1
#endif

#ifndef FIMSRG_PATCH_VERSION
#define FIMSRG_PATCH_VERSION -1
#endif

TEST_CASE("Test MajorVersion matches externally defined value.") {
  REQUIRE(fimsrg::MajorVersion() == FIMSRG_MAJOR_VERSION);
}

TEST_CASE("Test MinorVersion matches externally defined value.") {
  REQUIRE(fimsrg::MinorVersion() == FIMSRG_MINOR_VERSION);
}

TEST_CASE("Test PatchVersion matches externally defined value.") {
  REQUIRE(fimsrg::PatchVersion() == FIMSRG_PATCH_VERSION);
}

TEST_CASE("Test VersionString matches expected form.") {
  const auto version_string = fimsrg::VersionString();

  const std::vector<std::string> split_version_string =
      absl::StrSplit(version_string, ".");

  REQUIRE(split_version_string.size() == 3);
  REQUIRE(std::stoi(split_version_string[0]) == fimsrg::MajorVersion());
  REQUIRE(std::stoi(split_version_string[1]) == fimsrg::MinorVersion());
  REQUIRE(std::stoi(split_version_string[2]) == fimsrg::PatchVersion());
}
