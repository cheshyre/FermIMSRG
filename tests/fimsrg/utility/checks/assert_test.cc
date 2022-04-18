// Copyright 2022 Matthias Heinz
#include "fimsrg/utility/checks/assert.h"

#include "catch2/catch.hpp"

// We need this macro because catch requires its argument to be a single
// expression, which does not play well with Expects, Assert, and Ensures, which
// are all macros.
#define LAMBDA_EXPAND(x) [&]() { x; }()

TEST_CASE("Test Expects() on false conditions.") {
  if (fimsrg::RuntimeChecksEnabled()) {
    REQUIRE_THROWS(LAMBDA_EXPAND(Expects(1 < 0)));
    REQUIRE_THROWS(LAMBDA_EXPAND(Expects(1 == 0)));
    REQUIRE_THROWS(LAMBDA_EXPAND(Expects(1.0 == 0.0)));
    REQUIRE_THROWS(
        LAMBDA_EXPAND(Expects(std::string("foo") == std::string("bar"))));
  } else {
    REQUIRE_NOTHROW(LAMBDA_EXPAND(Expects(1 < 0)));
    REQUIRE_NOTHROW(LAMBDA_EXPAND(Expects(1 == 0)));
    REQUIRE_NOTHROW(LAMBDA_EXPAND(Expects(1.0 == 0.0)));
    REQUIRE_NOTHROW(
        LAMBDA_EXPAND(Expects(std::string("foo") == std::string("bar"))));
  }
}

TEST_CASE("Test Assert() on false conditions.") {
  if (fimsrg::RuntimeChecksEnabled()) {
    REQUIRE_THROWS(LAMBDA_EXPAND(Assert(1 < 0)));
    REQUIRE_THROWS(LAMBDA_EXPAND(Assert(1 == 0)));
    REQUIRE_THROWS(LAMBDA_EXPAND(Assert(1.0 == 0.0)));
    REQUIRE_THROWS(
        LAMBDA_EXPAND(Assert(std::string("foo") == std::string("bar"))));
  } else {
    REQUIRE_NOTHROW(LAMBDA_EXPAND(Assert(1 < 0)));
    REQUIRE_NOTHROW(LAMBDA_EXPAND(Assert(1 == 0)));
    REQUIRE_NOTHROW(LAMBDA_EXPAND(Assert(1.0 == 0.0)));
    REQUIRE_NOTHROW(
        LAMBDA_EXPAND(Assert(std::string("foo") == std::string("bar"))));
  }
}

TEST_CASE("Test Ensures() on false conditions.") {
  if (fimsrg::RuntimeChecksEnabled()) {
    REQUIRE_THROWS(LAMBDA_EXPAND(Ensures(1 < 0)));
    REQUIRE_THROWS(LAMBDA_EXPAND(Ensures(1 == 0)));
    REQUIRE_THROWS(LAMBDA_EXPAND(Ensures(1.0 == 0.0)));
    REQUIRE_THROWS(
        LAMBDA_EXPAND(Ensures(std::string("foo") == std::string("bar"))));
  } else {
    REQUIRE_NOTHROW(LAMBDA_EXPAND(Ensures(1 < 0)));
    REQUIRE_NOTHROW(LAMBDA_EXPAND(Ensures(1 == 0)));
    REQUIRE_NOTHROW(LAMBDA_EXPAND(Ensures(1.0 == 0.0)));
    REQUIRE_NOTHROW(
        LAMBDA_EXPAND(Ensures(std::string("foo") == std::string("bar"))));
  }
}

TEST_CASE("Test Expects() on true conditions.") {
  REQUIRE_NOTHROW(LAMBDA_EXPAND(Expects(1 > 0)));
  REQUIRE_NOTHROW(LAMBDA_EXPAND(Expects(1 == 1)));
  REQUIRE_NOTHROW(LAMBDA_EXPAND(Expects(-0.4 < 0.0)));
  REQUIRE_NOTHROW(
      LAMBDA_EXPAND(Expects(std::string("foo") != std::string("bar"))));
}

TEST_CASE("Test Assert() on true conditions.") {
  REQUIRE_NOTHROW(LAMBDA_EXPAND(Assert(1 > 0)));
  REQUIRE_NOTHROW(LAMBDA_EXPAND(Assert(1 == 1)));
  REQUIRE_NOTHROW(LAMBDA_EXPAND(Assert(-0.4 < 0.0)));
  REQUIRE_NOTHROW(
      LAMBDA_EXPAND(Assert(std::string("foo") != std::string("bar"))));
}

TEST_CASE("Test Ensures() on true conditions.") {
  REQUIRE_NOTHROW(LAMBDA_EXPAND(Ensures(1 > 0)));
  REQUIRE_NOTHROW(LAMBDA_EXPAND(Ensures(1 == 1)));
  REQUIRE_NOTHROW(LAMBDA_EXPAND(Ensures(-0.4 < 0.0)));
  REQUIRE_NOTHROW(
      LAMBDA_EXPAND(Ensures(std::string("foo") != std::string("bar"))));
}
