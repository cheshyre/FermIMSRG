// Copyright 2022 Matthias Heinz
#include "fimsrg/tensor/data/internal/data_buffer.h"

// IWYU pragma: no_include <built-in>
// IWYU pragma: no_include <unordered_map>
#include <cstddef>
#include <initializer_list>
#include <type_traits>
#include <utility>
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

inline DataBuffer DataBufferFromDataVector(
    const std::vector<double>& data_vec) {
  DataBuffer buf(data_vec.size());

  for (std::size_t i = 0; i < buf.size(); i += 1) {
    buf.at(i) = data_vec[i];
  }

  return buf;
}

TEST_CASE("Test default constructor.") {
  REQUIRE(std::is_nothrow_default_constructible_v<DataBuffer>);

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

TEST_CASE("Test copy constructor (empty).") {
  DataBuffer empty;

  DataBuffer empty_copy(empty);

  REQUIRE(empty_copy.size() == 0);
  REQUIRE(empty_copy.data() == nullptr);
}

TEST_CASE("Test copy constructor (nonempty).") {
  REQUIRE(std::is_copy_constructible_v<DataBuffer>);

  for (const std::vector<double>& ref_data :
       {DataVector1(), DataVector2(), DataVector3()}) {
    DataBuffer orig = DataBufferFromDataVector((ref_data));
    DataBuffer copy(orig);

    // Same size
    REQUIRE(copy.size() == orig.size());
    // But new buffer
    REQUIRE(copy.data() != orig.data());
    // With same data
    for (std::size_t i = 0; i < copy.size(); i += 1) {
      REQUIRE(copy.at(i) == orig.at(i));
    }
  }
}

TEST_CASE("Test move constructor (empty).") {
  DataBuffer empty;

  DataBuffer empty_copy(std::move(empty));

  REQUIRE(empty_copy.size() == 0);
  REQUIRE(empty_copy.data() == nullptr);
}

TEST_CASE("Test move constructor (nonempty).") {
  REQUIRE(std::is_nothrow_move_constructible_v<DataBuffer>);

  for (const std::vector<double>& ref_data :
       {DataVector1(), DataVector2(), DataVector3()}) {
    DataBuffer orig = DataBufferFromDataVector((ref_data));

    // Save relevant members because orig will be modified by move
    std::size_t orig_size = orig.size();
    double* orig_data_ptr = orig.data();

    DataBuffer copy(std::move(orig));

    // Same size
    REQUIRE(copy.size() == orig_size);
    // And same buffer
    REQUIRE(copy.data() == orig_data_ptr);
    // With same data
    for (std::size_t i = 0; i < copy.size(); i += 1) {
      REQUIRE(copy.at(i) == ref_data[i]);
    }

    // Orig should not have the pointer to the buffer
    REQUIRE(orig.data() != orig_data_ptr);
  }
}

TEST_CASE("Test copy assignment (empty).") {
  DataBuffer empty;

  DataBuffer empty_copy;

  REQUIRE(empty_copy.size() == 0);
  REQUIRE(empty_copy.data() == nullptr);

  empty_copy = empty;

  REQUIRE(empty_copy.size() == 0);
  REQUIRE(empty_copy.data() == nullptr);
}

TEST_CASE("Test copy assignment (nonempty).") {
  REQUIRE(std::is_copy_assignable_v<DataBuffer>);

  for (const std::vector<double>& ref_data :
       {DataVector1(), DataVector2(), DataVector3()}) {
    DataBuffer orig = DataBufferFromDataVector((ref_data));
    DataBuffer copy;

    REQUIRE(copy.size() == 0);
    REQUIRE(copy.data() == nullptr);

    copy = orig;

    // Same size
    REQUIRE(copy.size() == orig.size());
    // But new buffer
    REQUIRE(copy.data() != orig.data());
    // With same data
    for (std::size_t i = 0; i < copy.size(); i += 1) {
      REQUIRE(copy.at(i) == orig.at(i));
    }
  }
}

TEST_CASE("Test move assignment (empty).") {
  DataBuffer empty;

  DataBuffer empty_copy;

  REQUIRE(empty_copy.size() == 0);
  REQUIRE(empty_copy.data() == nullptr);

  empty_copy = std::move(empty);

  REQUIRE(empty_copy.size() == 0);
  REQUIRE(empty_copy.data() == nullptr);
}

TEST_CASE("Test move assignment (nonempty).") {
  REQUIRE(std::is_nothrow_move_assignable_v<DataBuffer>);

  for (const std::vector<double>& ref_data :
       {DataVector1(), DataVector2(), DataVector3()}) {
    DataBuffer orig = DataBufferFromDataVector((ref_data));

    // Save relevant members because orig will be modified by move
    std::size_t orig_size = orig.size();
    double* orig_data_ptr = orig.data();

    DataBuffer copy;

    REQUIRE(copy.size() == 0);
    REQUIRE(copy.data() == nullptr);

    copy = std::move(orig);

    // Same size
    REQUIRE(copy.size() == orig_size);
    // And same buffer
    REQUIRE(copy.data() == orig_data_ptr);
    // With same data
    for (std::size_t i = 0; i < copy.size(); i += 1) {
      REQUIRE(copy.at(i) == ref_data[i]);
    }

    // Orig should not have the pointer to the buffer
    REQUIRE(orig.data() != orig_data_ptr);
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

TEST_CASE("Test member swap.") {
  REQUIRE(std::is_nothrow_swappable_v<DataBuffer>);

  for (const DataBuffer& a : {DataBufferFromDataVector(DataVector1()),
                              DataBufferFromDataVector(DataVector2()),
                              DataBufferFromDataVector(DataVector3())}) {
    for (const DataBuffer& b : {DataBufferFromDataVector(DataVector1()),
                                DataBufferFromDataVector(DataVector2()),
                                DataBufferFromDataVector(DataVector3())}) {
      DataBuffer a_copy(a);
      double* a_copy_buf_ptr = a_copy.data();

      DataBuffer b_copy(b);
      double* b_copy_buf_ptr = b_copy.data();

      REQUIRE(a_copy.size() == a.size());
      REQUIRE(b_copy.size() == b.size());

      a_copy.swap(b_copy);

      REQUIRE(b_copy.size() == a.size());
      REQUIRE(b_copy.data() == a_copy_buf_ptr);
      REQUIRE(a_copy.size() == b.size());
      REQUIRE(a_copy.data() == b_copy_buf_ptr);

      b_copy.swap(a_copy);

      REQUIRE(a_copy.size() == a.size());
      REQUIRE(a_copy.data() == a_copy_buf_ptr);
      REQUIRE(b_copy.size() == b.size());
      REQUIRE(b_copy.data() == b_copy_buf_ptr);
    }
  }
}

TEST_CASE("Test nonmember swap.") {
  REQUIRE(std::is_nothrow_swappable_v<DataBuffer>);

  for (const DataBuffer& a : {DataBufferFromDataVector(DataVector1()),
                              DataBufferFromDataVector(DataVector2()),
                              DataBufferFromDataVector(DataVector3())}) {
    for (const DataBuffer& b : {DataBufferFromDataVector(DataVector1()),
                                DataBufferFromDataVector(DataVector2()),
                                DataBufferFromDataVector(DataVector3())}) {
      using std::swap;

      DataBuffer a_copy(a);
      double* a_copy_buf_ptr = a_copy.data();

      DataBuffer b_copy(b);
      double* b_copy_buf_ptr = b_copy.data();

      REQUIRE(a_copy.size() == a.size());
      REQUIRE(b_copy.size() == b.size());

      swap(a_copy, b_copy);

      REQUIRE(b_copy.size() == a.size());
      REQUIRE(b_copy.data() == a_copy_buf_ptr);
      REQUIRE(a_copy.size() == b.size());
      REQUIRE(a_copy.data() == b_copy_buf_ptr);

      swap(b_copy, a_copy);

      REQUIRE(a_copy.size() == a.size());
      REQUIRE(a_copy.data() == a_copy_buf_ptr);
      REQUIRE(b_copy.size() == b.size());
      REQUIRE(b_copy.data() == b_copy_buf_ptr);
    }
  }
}
