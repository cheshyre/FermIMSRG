// Copyright 2022 Matthias Heinz
#include "fimsrg/tensor/data/internal/data_buffer.h"

// IWYU pragma: no_include <built-in>
#include <cstddef>
#include <initializer_list>

#include "catch2/catch.hpp"

using fimsrg::internal::DataBuffer;

TEST_CASE("Test default constructor.") {
  DataBuffer data_buffer;

  REQUIRE(data_buffer.size() == 0);
  REQUIRE(data_buffer.data() == nullptr);
}

TEST_CASE("Test standard constructor and size().") {
  for (const std::size_t size : {0, 1, 2, 3, 4, 8, 24, 64, 1000}) {
    DataBuffer data_buffer(size);

    REQUIRE(data_buffer.size() == size);
  }
}

TEST_CASE("Test standard constructor and at() for const buffer.") {
  for (const std::size_t size : {0, 1, 2, 3, 4, 8, 24, 64, 1000}) {
    const DataBuffer data_buffer(size);

    for (std::size_t index = 0; index < size; index += 1) {
      REQUIRE(data_buffer.at(index) == 0.0);
    }
  }
}

TEST_CASE("Test standard constructor and at() for nonconst buffer.") {
  for (const std::size_t size : {0, 1, 2, 3, 4, 8, 24, 64, 1000}) {
    DataBuffer data_buffer(size);

    for (std::size_t index = 0; index < size; index += 1) {
      REQUIRE(data_buffer.at(index) == 0.0);
    }
  }
}

TEST_CASE("Test standard constructor and data() for nonempty.") {
  for (const std::size_t size : {1, 2, 3, 4, 8, 24, 64, 1000}) {
    DataBuffer data_buffer(size);

    REQUIRE(data_buffer.data() != nullptr);
  }
}

TEST_CASE("Test standard constructor and data() for empty.") {
  for (const std::size_t size : {0}) {
    DataBuffer data_buffer(size);

    REQUIRE(data_buffer.data() == nullptr);
  }
}
