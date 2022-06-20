// Copyright 2022 Matthias Heinz
#include "fimsrg/tensor/data/internal/data_buffer.h"

// IWYU pragma: no_include <built-in>
#include <cstddef>
#include <initializer_list>
#include <vector>

#include "catch2/catch.hpp"

using fimsrg::internal::DataBuffer;

inline std::vector<double> DataVector1() {
  return {0.0, 1.0, 2.0, 3.0, 4.0, 5.0};
}

inline std::vector<double> DataVector2() {
  return {0.0, -1.0, -2.0, -3.0, -4.0, -5.0};
}

inline std::vector<double> DataVector3() {
  return {1.0,           -0.5, 1.0 / 6,        0.0, -1.0 / 30,     0.0,
          1.0 / 42,      0.0,  -1.0 / 30,      0.0, 5.0 / 66,      0.0,
          -691.0 / 2730, 0.0,  7.0 / 6,        0.0, -3617.0 / 510, 0.0,
          43867.0 / 798, 0.0,  -174611.0 / 330};
}

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

TEST_CASE("Test at() (setter and getter) on nonconst.") {
  for (const std::vector<double>& ref_data :
       {DataVector1(), DataVector2(), DataVector3()}) {
    DataBuffer data_buffer(ref_data.size());

    REQUIRE(data_buffer.size() == ref_data.size());

    for (std::size_t index = 0; index < data_buffer.size(); index += 1) {
      REQUIRE(data_buffer.at(index) == 0.0);

      data_buffer.at(index) = ref_data[index];

      REQUIRE(data_buffer.at(index) == ref_data[index]);
    }

    // Second pass to test sequential collection nature of buffer
    for (std::size_t index = 0; index < data_buffer.size(); index += 1) {
      REQUIRE(data_buffer.at(index) == ref_data[index]);
    }
  }
}
