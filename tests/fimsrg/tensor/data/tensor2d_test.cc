// Copyright 2022 Matthias Heinz
#include "fimsrg/tensor/data/tensor2d.h"

// IWYU pragma: no_include <unordered_map>
#include <cstddef>
#include <initializer_list>
#include <type_traits>
#include <utility>  // IWYU pragma: keep

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

TEST_CASE("Test member addition of two random tensors.") {
  for (const std::size_t dim : {0, 1, 2, 4, 8, 10, 20}) {
    Tensor2D a = fimsrg::GenerateRandomTensor2D(dim);
    Tensor2D b = fimsrg::GenerateRandomTensor2D(dim);
    Tensor2D a_copy(a);

    a += b;

    REQUIRE(a.Dim() == dim);

    for (std::size_t i = 0; i < dim; i += 1) {
      for (std::size_t j = 0; j < dim; j += 1) {
        REQUIRE(a(i, j) == Approx(a_copy(i, j) + b(i, j)).margin(1e-8));
      }
    }
  }
}

TEST_CASE("Test member subtraction of two random tensors.") {
  for (const std::size_t dim : {0, 1, 2, 4, 8, 10, 20}) {
    Tensor2D a = fimsrg::GenerateRandomTensor2D(dim);
    Tensor2D b = fimsrg::GenerateRandomTensor2D(dim);
    Tensor2D a_copy(a);

    a -= b;

    REQUIRE(a.Dim() == dim);

    for (std::size_t i = 0; i < dim; i += 1) {
      for (std::size_t j = 0; j < dim; j += 1) {
        REQUIRE(a(i, j) == Approx(a_copy(i, j) - b(i, j)).margin(1e-8));
      }
    }
  }
}

TEST_CASE("Test member multiplication of random tensor by various factors.") {
  for (const double factor : {-0.1, 0.0, 2.0, 3.14}) {
    for (const std::size_t dim : {0, 1, 2, 4, 8, 10, 20}) {
      Tensor2D a = fimsrg::GenerateRandomTensor2D(dim);
      Tensor2D a_copy(a);

      a *= factor;

      REQUIRE(a.Dim() == dim);

      for (std::size_t i = 0; i < dim; i += 1) {
        for (std::size_t j = 0; j < dim; j += 1) {
          REQUIRE(a(i, j) == Approx(a_copy(i, j) * factor).margin(1e-8));
        }
      }
    }
  }
}

TEST_CASE("Test member division of random tensor by various nonzero factors.") {
  for (const double factor : {-0.1, 0.01, 2.0, 3.14}) {
    for (const std::size_t dim : {0, 1, 2, 4, 8, 10, 20}) {
      Tensor2D a = fimsrg::GenerateRandomTensor2D(dim);
      Tensor2D a_copy(a);

      a /= factor;

      REQUIRE(a.Dim() == dim);

      for (std::size_t i = 0; i < dim; i += 1) {
        for (std::size_t j = 0; j < dim; j += 1) {
          REQUIRE(a(i, j) == Approx(a_copy(i, j) / factor).margin(1e-8));
        }
      }
    }
  }
}

TEST_CASE("Test FrobeniusNorm on 2x2 matrix.") {
  Tensor2D a(2);

  a(0, 0) = 0.0;
  a(0, 1) = 2.0;
  a(1, 0) = -2.0;
  a(1, 1) = 9.0;

  REQUIRE(a.FrobeniusNorm() == Approx(89.0).margin(1e-8));
}

TEST_CASE("Test FrobeniusNorm on dim-by-dim matrices.") {
  for (const double val : {-0.1, 0.01, 2.0, 3.14}) {
    for (const std::size_t dim : {0, 1, 2, 4, 8, 10, 20}) {
      Tensor2D a = fimsrg::GenerateRandomTensor2D(dim);

      for (std::size_t i = 0; i < dim; i += 1) {
        for (std::size_t j = 0; j < dim; j += 1) {
          a(i, j) = val;
        }
      }

      REQUIRE(a.FrobeniusNorm() == Approx(dim * dim * val * val).margin(1e-8));
    }
  }
}

TEST_CASE("Test NumberOfElements() on random tensors.") {
  for (const std::size_t dim : {0, 1, 2, 4, 8, 10, 20}) {
    Tensor2D a = fimsrg::GenerateRandomTensor2D(dim);

    REQUIRE(a.NumberOfElements() == dim * dim);
  }
}

TEST_CASE("Test member swap on random tensors.") {
  REQUIRE(std::is_nothrow_swappable_v<Tensor2D>);

  for (const std::size_t dim_a : {0, 1, 2, 4, 8, 10, 20}) {
    const Tensor2D a_ref = fimsrg::GenerateRandomTensor2D(dim_a);
    for (const std::size_t dim_b : {0, 1, 2, 4, 8, 10, 20}) {
      const Tensor2D b_ref = fimsrg::GenerateRandomTensor2D(dim_b);

      Tensor2D a(a_ref);
      Tensor2D b(b_ref);

      a.swap(b);

      REQUIRE(a.Dim() == b_ref.Dim());
      REQUIRE(b.Dim() == a_ref.Dim());

      for (std::size_t i = 0; i < dim_a; i += 1) {
        for (std::size_t j = 0; j < dim_a; j += 1) {
          REQUIRE(b(i, j) == a_ref(i, j));
        }
      }

      for (std::size_t i = 0; i < dim_b; i += 1) {
        for (std::size_t j = 0; j < dim_b; j += 1) {
          REQUIRE(a(i, j) == b_ref(i, j));
        }
      }
    }
  }
}

TEST_CASE("Test nonmember swap on random tensors.") {
  REQUIRE(std::is_nothrow_swappable_v<Tensor2D>);

  for (const std::size_t dim_a : {0, 1, 2, 4, 8, 10, 20}) {
    const Tensor2D a_ref = fimsrg::GenerateRandomTensor2D(dim_a);
    for (const std::size_t dim_b : {0, 1, 2, 4, 8, 10, 20}) {
      const Tensor2D b_ref = fimsrg::GenerateRandomTensor2D(dim_b);

      Tensor2D a(a_ref);
      Tensor2D b(b_ref);

      using std::swap;
      swap(a, b);

      REQUIRE(a.Dim() == b_ref.Dim());
      REQUIRE(b.Dim() == a_ref.Dim());

      for (std::size_t i = 0; i < dim_a; i += 1) {
        for (std::size_t j = 0; j < dim_a; j += 1) {
          REQUIRE(b(i, j) == a_ref(i, j));
        }
      }

      for (std::size_t i = 0; i < dim_b; i += 1) {
        for (std::size_t j = 0; j < dim_b; j += 1) {
          REQUIRE(a(i, j) == b_ref(i, j));
        }
      }
    }
  }
}

TEST_CASE("Test nonmember addition of two random tensors.") {
  for (const std::size_t dim : {0, 1, 2, 4, 8, 10, 20}) {
    Tensor2D a = fimsrg::GenerateRandomTensor2D(dim);
    Tensor2D b = fimsrg::GenerateRandomTensor2D(dim);

    Tensor2D c = a + b;

    REQUIRE(c.Dim() == dim);

    for (std::size_t i = 0; i < dim; i += 1) {
      for (std::size_t j = 0; j < dim; j += 1) {
        REQUIRE(c(i, j) == Approx(a(i, j) + b(i, j)).margin(1e-8));
      }
    }
  }
}

TEST_CASE("Test nonmember subtraction of two random tensors.") {
  for (const std::size_t dim : {0, 1, 2, 4, 8, 10, 20}) {
    Tensor2D a = fimsrg::GenerateRandomTensor2D(dim);
    Tensor2D b = fimsrg::GenerateRandomTensor2D(dim);

    Tensor2D c = a - b;

    REQUIRE(c.Dim() == dim);

    for (std::size_t i = 0; i < dim; i += 1) {
      for (std::size_t j = 0; j < dim; j += 1) {
        REQUIRE(c(i, j) == Approx(a(i, j) - b(i, j)).margin(1e-8));
      }
    }
  }
}

TEST_CASE(
    "Test nonmember multiplication of random tensor by various factors.") {
  for (const double factor : {-0.1, 0.0, 2.0, 3.14}) {
    for (const std::size_t dim : {0, 1, 2, 4, 8, 10, 20}) {
      Tensor2D a = fimsrg::GenerateRandomTensor2D(dim);

      Tensor2D c = a * factor;
      Tensor2D c_prime = factor * a;

      REQUIRE(c.Dim() == dim);
      REQUIRE(c_prime.Dim() == dim);

      for (std::size_t i = 0; i < dim; i += 1) {
        for (std::size_t j = 0; j < dim; j += 1) {
          REQUIRE(c(i, j) == Approx(a(i, j) * factor).margin(1e-8));
          REQUIRE(c_prime(i, j) == Approx(a(i, j) * factor).margin(1e-8));
        }
      }
    }
  }
}

TEST_CASE(
    "Test nonmember division of random tensor by various nonzero factors.") {
  for (const double factor : {-0.1, 0.01, 2.0, 3.14}) {
    for (const std::size_t dim : {0, 1, 2, 4, 8, 10, 20}) {
      Tensor2D a = fimsrg::GenerateRandomTensor2D(dim);

      Tensor2D c = a / factor;

      REQUIRE(c.Dim() == dim);

      for (std::size_t i = 0; i < dim; i += 1) {
        for (std::size_t j = 0; j < dim; j += 1) {
          REQUIRE(c(i, j) == Approx(a(i, j) / factor).margin(1e-8));
        }
      }
    }
  }
}
