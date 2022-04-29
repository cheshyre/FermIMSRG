// Copyright 2022 Matthias Heinz
#include "fimsrg/utility/profiling/internal/single_event_profiler.h"

#include <cstdlib>
#include <memory>
#include <string>

// PRIVATE
#include "absl/strings/str_cat.h"
#include "absl/time/clock.h"

// PRIVATE
#include "fimsrg/utility/profiling/internal/profiling_database.h"

namespace fimsrg {
namespace internal {

std::unique_ptr<SingleEventProfiler>
SingleEventProfiler::MakeSingleEventProfiler(std::string event_name) {
  return std::make_unique<SingleEventProfiler>(event_name);
}

std::unique_ptr<SingleEventProfiler>
SingleEventProfiler::MakeSingleEventProfilerWithPrefix(std::string event_name,
                                                       std::string prefix) {
  return std::make_unique<SingleEventProfiler>(
      absl::StrCat(event_name, ", prefix = ", prefix));
}

std::unique_ptr<SingleEventProfiler>
SingleEventProfiler::MakeSingleEventProfilerWithSize(std::string event_name,
                                                     std::size_t size) {
  return std::make_unique<SingleEventProfiler>(
      absl::StrCat(event_name, ", size = ", std::to_string(size)));
}

std::unique_ptr<SingleEventProfiler>
SingleEventProfiler::MakeSingleEventProfilerWithPrefixAndSize(
    std::string event_name, std::string prefix, std::size_t size) {
  return std::make_unique<SingleEventProfiler>(absl::StrCat(
      event_name, ", prefix = ", prefix, ", size = ", std::to_string(size)));
}

SingleEventProfiler::SingleEventProfiler(std::string event_name)
    : event_name_(event_name), start_time_ns_(absl::GetCurrentTimeNanos()) {}

SingleEventProfiler::~SingleEventProfiler() {
  const auto end_time_ns = absl::GetCurrentTimeNanos();
  auto& prof_db = ProfilingDatabase::GetInstance();
  double elapsed_time_s = (end_time_ns - start_time_ns_) / 1e9;
  prof_db.AddProfilingEvent({event_name_, elapsed_time_s});
}

}  // namespace internal
}  // namespace fimsrg
