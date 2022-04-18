// Copyright 2022 Matthias Heinz
#ifndef FIMSRG_UTILITY_PROFILING_INTERNAL_PROFILING_DATA_H_
#define FIMSRG_UTILITY_PROFILING_INTERNAL_PROFILING_DATA_H_

#include <cstdlib>
#include <string>
#include <utility>

#include "fimsrg/utility/profiling/internal/profiling_event_data.h"

namespace fimsrg {
namespace internal {

// Collected profiling data across multiple events.
struct ProfilingData {
  std::string event_name = "";
  std::size_t event_count = 0;
  double wall_time = 0.0;

  // Add single profiling event to the current collection.
  //
  // Requires both to have the same event_name.
  // A notable exception is if the event_name in ProfilingData is "".
  // Then, it will take on the event_name of the profiling event.
  void AddProfilingEvent(const ProfilingEventData& event_data);
};

// Swap profiling data.
inline void swap(ProfilingData& a, ProfilingData& b) noexcept {
  using std::swap;
  swap(a.event_name, b.event_name);
  swap(a.event_count, b.event_count);
  swap(a.wall_time, b.wall_time);
}

// Determine whether profiiling data a is less expensive than b.
//
// Gives a total ordering to profiling data for reports.
bool operator<(const ProfilingData& a, const ProfilingData& b);

}  // namespace internal
}  // namespace fimsrg

#endif  // FIMSRG_UTILITY_PROFILING_INTERNAL_PROFILING_DATA_H_
