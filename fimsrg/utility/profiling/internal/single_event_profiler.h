// Copyright 2022 Matthias Heinz
#ifndef FIMSRG_UTILITY_PROFILING_INTERNAL_SINGLE_EVENT_PROFILER_H_
#define FIMSRG_UTILITY_PROFILING_INTERNAL_SINGLE_EVENT_PROFILER_H_

#include <cstdint>
#include <cstdlib>
#include <memory>
#include <string>

namespace fimsrg {
namespace internal {

class SingleEventProfiler {
 public:
  // Create a unique single event profiler for a given event.
  static std::unique_ptr<SingleEventProfiler> MakeSingleEventProfiler(
      std::string event_name);

  // Create a unique single event profiler for an event with a specified size.
  static std::unique_ptr<SingleEventProfiler> MakeSingleEventProfilerWithSize(
      std::string event_name, std::size_t size);

  // Constructor.
  //
  // You should probably not call this directly.
  // Prefer the factor function MakeSingleEventProfiler(event_name).
  explicit SingleEventProfiler(std::string event_name);

  // Destructor.
  ~SingleEventProfiler();

  // Cannot be copied.
  SingleEventProfiler(const SingleEventProfiler&) = delete;

  // Cannot be copied.
  void operator=(const SingleEventProfiler&) = delete;

  // Cannot be moved.
  SingleEventProfiler(SingleEventProfiler&&) = delete;

  // Cannot be moved.
  void operator=(SingleEventProfiler&&) = delete;

 private:
  std::string event_name_;
  std::int64_t start_time_ns_;
};

}  // namespace internal
}  // namespace fimsrg

#endif  // FIMSRG_UTILITY_PROFILING_INTERNAL_SINGLE_EVENT_PROFILER_H_
