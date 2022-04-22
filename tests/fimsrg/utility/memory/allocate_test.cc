// Copyright 2022 Matthias Heinz
#include "fimsrg/utility/memory/allocate.h"

#include <cstdint>
#include <cstdlib>

#include "catch2/catch.hpp"

TEMPLATE_TEST_CASE("Test basic allocate/deallocate.", "", int, double,
                   std::int64_t) {
  for (const std::size_t size : {4, 64, 1024}) {
    const auto p1 = fimsrg::Allocate<TestType>(size);
    const auto p2 = fimsrg::Allocate<TestType>(size);
    const auto p3 = fimsrg::Allocate<TestType>(size);

    REQUIRE(p1 != p2);
    REQUIRE(p1 != p3);
    REQUIRE(p2 != p3);

    fimsrg::Deallocate<TestType>(p1, size);
    fimsrg::Deallocate<TestType>(p2, size);
    fimsrg::Deallocate<TestType>(p3, size);
  }
}

TEMPLATE_TEST_CASE("Test pooled allocate/deallocate.", "", int, double,
                   std::int64_t) {
  for (const std::size_t size : {4, 64, 1024}) {
    const auto p1 = fimsrg::PooledAllocate<TestType>(size);
    const auto p2 = fimsrg::PooledAllocate<TestType>(size);
    const auto p3 = fimsrg::PooledAllocate<TestType>(size);

    REQUIRE(p1 != p2);
    REQUIRE(p1 != p3);
    REQUIRE(p2 != p3);

    fimsrg::PooledDeallocate<TestType>(p1, size);
    fimsrg::PooledDeallocate<TestType>(p2, size);
    fimsrg::PooledDeallocate<TestType>(p3, size);
  }
}

TEMPLATE_TEST_CASE("Test reuse in pooled allocate/deallocate.", "", int, double,
                   std::int64_t) {
  for (const std::size_t size : {4, 64, 1024}) {
    const auto p1 = fimsrg::PooledAllocate<TestType>(size);
    const auto p2 = fimsrg::PooledAllocate<TestType>(size);
    const auto p3 = fimsrg::PooledAllocate<TestType>(size);

    REQUIRE(p1 != p2);
    REQUIRE(p1 != p3);
    REQUIRE(p2 != p3);

    fimsrg::PooledDeallocate<TestType>(p3, size);
    const auto p4 = fimsrg::PooledAllocate<TestType>(size);

    REQUIRE(p4 == p3);

    fimsrg::PooledDeallocate<TestType>(p1, size);
    fimsrg::PooledDeallocate<TestType>(p2, size);
    fimsrg::PooledDeallocate<TestType>(p4, size);
  }
}
