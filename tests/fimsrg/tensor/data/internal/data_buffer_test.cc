// Copyright 2022 Matthias Heinz
#include "fimsrg/tensor/data/internal/data_buffer.h"

// IWYU pragma: no_include <built-in>

#include "catch2/catch.hpp"

TEST_CASE("Test default constructor.") {
  fimsrg::internal::DataBuffer data_buffer;

  REQUIRE(data_buffer.size() == 0);
  REQUIRE(data_buffer.data() == nullptr);
}
