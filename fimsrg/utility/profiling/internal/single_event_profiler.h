// Copyright 2022 Matthias Heinz
#ifndef FIMSRG_UTILITY_PROFILING_INTERNAL_SINGLE_EVENT_PROFILER_H_
#define FIMSRG_UTILITY_PROFILING_INTERNAL_SINGLE_EVENT_PROFILER_H_

#include <cstdint>
#include <cstdlib>
#include <memory>
#include <string>

namespace fimsrg {
namespace internal {

// Class to automatically profile a function via the RAII principle.
//
// Construction of a SingleEventProfiler via a factory method
// marks the start of the profiling event.
// Upon destruction at the end of the context,
// the profiler will report back to the profiling database.
class SingleEventProfiler {
 public:
  // Create a unique single event profiler for a given event.
  static std::unique_ptr<SingleEventProfiler> MakeSingleEventProfiler(
      std::string event_name);

  // Create a unique single event profiler for a given event with a specified
  // prefix.
  //
  // This is used to resolve between different overloads.
  static std::unique_ptr<SingleEventProfiler> MakeSingleEventProfilerWithPrefix(
      std::string event_name, std::string prefix);

  // Create a unique single event profiler for an event with a specified size.
  static std::unique_ptr<SingleEventProfiler> MakeSingleEventProfilerWithSize(
      std::string event_name, std::size_t size);

  // Create a unique single event profiler for an event with a specified prefix
  // and a specified size.
  //
  // This is used to resolve between different overloads.
  static std::unique_ptr<SingleEventProfiler>
  MakeSingleEventProfilerWithPrefixAndSize(std::string event_name,
                                           std::string prefix,
                                           std::size_t size);

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
