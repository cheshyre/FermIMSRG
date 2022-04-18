// Copyright 2022 Matthias Heinz
#include "fimsrg/utility/checks/error.h"

#include <string>

#include "catch2/catch.hpp"

TEST_CASE("Test CheckForError() on valid cases.") {
  SECTION("using ValidationResult") {
    REQUIRE_NOTHROW(fimsrg::CheckForError(
        fimsrg::ValidationResult{0 < 1, ErrorMessage("Valid case 1")}));
    REQUIRE_NOTHROW(fimsrg::CheckForError(
        fimsrg::ValidationResult{std::string("asdf") != std::string("qwerty"),
                                 ErrorMessage("Valid case 2")}));
    REQUIRE_NOTHROW(fimsrg::CheckForError(
        fimsrg::ValidationResult{true, ErrorMessage("Valid case 3")}));
    REQUIRE_NOTHROW(fimsrg::CheckForError(
        fimsrg::ValidationResult{1.0 > 0.5, ErrorMessage("Valid case 4")}));
  }
  SECTION("using bool, string_view") {
    REQUIRE_NOTHROW(fimsrg::CheckForError(0 > 1, ErrorMessage("Valid case 1")));
    REQUIRE_NOTHROW(
        fimsrg::CheckForError(std::string("asdf") == std::string("qwerty"),
                              ErrorMessage("Valid case 2")));
    REQUIRE_NOTHROW(fimsrg::CheckForError(false, ErrorMessage("Valid case 3")));
    REQUIRE_NOTHROW(
        fimsrg::CheckForError(1.0 < 0.5, ErrorMessage("Valid case 4")));
  }
}

TEST_CASE("Test CheckForError() on invalid cases.") {
  SECTION("using ValidationResult") {
    REQUIRE_THROWS(fimsrg::CheckForError(
        fimsrg::ValidationResult{0 > 1, ErrorMessage("Invalid case 1")}));
    REQUIRE_THROWS(fimsrg::CheckForError(
        fimsrg::ValidationResult{std::string("asdf") == std::string("qwerty"),
                                 ErrorMessage("Invalid case 2")}));
    REQUIRE_THROWS(fimsrg::CheckForError(
        fimsrg::ValidationResult{false, ErrorMessage("Invalid case 3")}));
    REQUIRE_THROWS(fimsrg::CheckForError(
        fimsrg::ValidationResult{1.0 < 0.5, ErrorMessage("Invalid case 4")}));
  }
  SECTION("using using bool, string_view") {
    REQUIRE_THROWS(
        fimsrg::CheckForError(0 < 1, ErrorMessage("Invalid case 1")));
    REQUIRE_THROWS(
        fimsrg::CheckForError(std::string("asdf") != std::string("qwerty"),
                              ErrorMessage("Invalid case 2")));
    REQUIRE_THROWS(fimsrg::CheckForError(true, ErrorMessage("Invalid case 3")));
    REQUIRE_THROWS(
        fimsrg::CheckForError(1.0 > 0.5, ErrorMessage("Invalid case 4")));
  }
}
