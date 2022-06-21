// Copyright 2022 Matthias Heinz
#include "fimsrg/tensor/data/tensor2d.h"

#include <cstddef>
#include <initializer_list>
#include <type_traits>

#include "fimsrg/tensor/random/tensor2d.h"
#include "fimsrg/utility/memory/alignment.h"

#include "catch2/catch.hpp"

using fimsrg::Tensor2D;

inline double SampleMatrixElementValue(std::size_t i, std::size_t j) {
  return 1.0 * (1000 * i + j) - 2000.0;
}

TEST_CASE("Test factory method on zero-initialized tensors.") {
  for (const std::size_t dim : {0, 1, 2, 4, 8, 10, 20}) {
    Tensor2D ref_t2(dim);

    const Tensor2D new_t2 = Tensor2D::ZerosLike(ref_t2);

    REQUIRE(new_t2.Dim() == dim);
    REQUIRE(new_t2.CheckInvariants());

    for (std::size_t i = 0; i < dim; i += 1) {
      for (std::size_t j = 0; j < dim; j += 1) {
        REQUIRE(new_t2(i, j) == 0.0);
      }
    }
  }
}

TEST_CASE("Test factory method on random tensors.") {
  for (const std::size_t dim : {0, 1, 2, 4, 8, 10, 20}) {
    Tensor2D ref_t2 = fimsrg::GenerateRandomTensor2D(dim);

    const Tensor2D new_t2 = Tensor2D::ZerosLike(ref_t2);

    REQUIRE(new_t2.Dim() == dim);
    REQUIRE(new_t2.CheckInvariants());

    for (std::size_t i = 0; i < dim; i += 1) {
      for (std::size_t j = 0; j < dim; j += 1) {
        REQUIRE(new_t2(i, j) == 0.0);
      }
    }
  }
}

TEST_CASE("Test default constructor.") {
  REQUIRE(std::is_nothrow_default_constructible_v<Tensor2D>);

  Tensor2D tens;

  REQUIRE(tens.Dim() == 0);
  REQUIRE(tens.CheckInvariants());
  REQUIRE(tens.data() == nullptr);
}

TEST_CASE("Test standard constructor and Dim().") {
  for (const std::size_t dim : {0, 1, 2, 4, 8, 10, 20}) {
    Tensor2D t2(dim);

    REQUIRE(t2.Dim() == dim);
  }
}

TEST_CASE("Test standard constructor and StrideI().") {
  using fimsrg::GetMinimumAlignment;

  for (const std::size_t dim : {0, 1, 2, 4, 8, 10, 20}) {
    Tensor2D t2(dim);

    REQUIRE((t2.StrideI() * sizeof(double)) % GetMinimumAlignment() == 0);
  }
}

TEST_CASE("Test standard constructor, CheckInvariants(), and operator().") {
  for (const std::size_t dim : {0, 1, 2, 4, 8, 10, 20}) {
    Tensor2D t2(dim);

    REQUIRE(t2.CheckInvariants());

    for (std::size_t i = 0; i < dim; i += 1) {
      for (std::size_t j = 0; j < dim; j += 1) {
        REQUIRE(t2(i, j) == 0.0);
      }
    }
  }
}

TEST_CASE("Test copy constructor on nonempty random tensors.") {
  REQUIRE(std::is_copy_constructible_v<Tensor2D>);

  for (const std::size_t dim : {1, 2, 4, 8, 10, 20}) {
    Tensor2D ref_t2 = fimsrg::GenerateRandomTensor2D(dim);

    const Tensor2D new_t2(ref_t2);

    REQUIRE(new_t2.Dim() == dim);
    REQUIRE(new_t2.CheckInvariants());
    // No shallow copy
    REQUIRE(new_t2.data() != ref_t2.data());

    for (std::size_t i = 0; i < dim; i += 1) {
      for (std::size_t j = 0; j < dim; j += 1) {
        REQUIRE(new_t2(i, j) == Approx(ref_t2(i, j)).margin(1e-8));
      }
    }
  }
}

TEST_CASE("Test move constructor on nonempty random tensors.") {
  REQUIRE(std::is_nothrow_move_constructible_v<Tensor2D>);

  for (const std::size_t dim : {1, 2, 4, 8, 10, 20}) {
    Tensor2D ref_t2 = fimsrg::GenerateRandomTensor2D(dim);
    // save ptr for later
    double* ref_t2_data_ptr = ref_t2.data();

    const Tensor2D ref_t2_copy(ref_t2);

    const Tensor2D new_t2(std::move(ref_t2));

    REQUIRE(new_t2.Dim() == dim);
    REQUIRE(new_t2.CheckInvariants());
    // ref_t2 should no longer have the saved ptr
    REQUIRE(new_t2.data() != ref_t2.data());
    REQUIRE(new_t2.data() == ref_t2_data_ptr);

    for (std::size_t i = 0; i < dim; i += 1) {
      for (std::size_t j = 0; j < dim; j += 1) {
        REQUIRE(new_t2(i, j) == Approx(ref_t2_copy(i, j)).margin(1e-8));
      }
    }
  }
}

TEST_CASE("Test copy assignment on nonempty random tensors.") {
  REQUIRE(std::is_copy_assignable_v<Tensor2D>);

  for (const std::size_t orig_dim : {1, 2, 4, 8, 10, 20}) {
    Tensor2D new_t2 = fimsrg::GenerateRandomTensor2D(orig_dim);
    for (const std::size_t dim : {1, 2, 4, 8, 10, 20}) {
      Tensor2D ref_t2 = fimsrg::GenerateRandomTensor2D(dim);

      new_t2 = ref_t2;

      REQUIRE(new_t2.Dim() == dim);
      REQUIRE(new_t2.CheckInvariants());
      // No shallow copy
      REQUIRE(new_t2.data() != ref_t2.data());

      for (std::size_t i = 0; i < dim; i += 1) {
        for (std::size_t j = 0; j < dim; j += 1) {
          REQUIRE(new_t2(i, j) == Approx(ref_t2(i, j)).margin(1e-8));
        }
      }
    }
  }
}

TEST_CASE("Test move assignment on nonempty random tensors.") {
  REQUIRE(std::is_nothrow_move_assignable_v<Tensor2D>);

  for (const std::size_t orig_dim : {1, 2, 4, 8, 10, 20}) {
    Tensor2D new_t2 = fimsrg::GenerateRandomTensor2D(orig_dim);
    for (const std::size_t dim : {1, 2, 4, 8, 10, 20}) {
      Tensor2D ref_t2 = fimsrg::GenerateRandomTensor2D(dim);
      // save ptr for later
      double* ref_t2_data_ptr = ref_t2.data();

      const Tensor2D ref_t2_copy(ref_t2);

      new_t2 = std::move(ref_t2);

      REQUIRE(new_t2.Dim() == dim);
      REQUIRE(new_t2.CheckInvariants());
      // ref_t2 should no longer have the saved ptr
      REQUIRE(new_t2.data() != ref_t2.data());
      REQUIRE(new_t2.data() == ref_t2_data_ptr);

      for (std::size_t i = 0; i < dim; i += 1) {
        for (std::size_t j = 0; j < dim; j += 1) {
          REQUIRE(new_t2(i, j) == Approx(ref_t2_copy(i, j)).margin(1e-8));
        }
      }
    }
  }
}

TEST_CASE("Test operator() (setter and getter).") {
  for (const std::size_t dim : {0, 1, 2, 4, 8, 10, 20}) {
    Tensor2D t2(dim);

    for (std::size_t i = 0; i < dim; i += 1) {
      for (std::size_t j = 0; j < dim; j += 1) {
        t2(i, j) = SampleMatrixElementValue(i, j);
        REQUIRE(t2(i, j) == SampleMatrixElementValue(i, j));
      }
    }

    for (std::size_t i = 0; i < dim; i += 1) {
      for (std::size_t j = 0; j < dim; j += 1) {
        REQUIRE(t2(i, j) == SampleMatrixElementValue(i, j));
      }
    }
  }
}

// TODO(mheinz): Test arithmetic ops

// TODO(mheinz): Test swaps

// TODO(mheinz): Test arithmetic ops
