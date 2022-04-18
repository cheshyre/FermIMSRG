// Copyright 2022 Matthias Heinz
#ifndef FIMSRG_UTILITY_PROFILING_INTERNAL_PROFILING_EVENT_DATA_H_
#define FIMSRG_UTILITY_PROFILING_INTERNAL_PROFILING_EVENT_DATA_H_

#include <string>
#include <utility>

namespace fimsrg {
namespace internal {

// Data for a single profiling event.
struct ProfilingEventData {
  std::string event_name = "";
  double wall_time = 0.0;
};

// Swap two profiling event data.
inline void swap(ProfilingEventData& a, ProfilingEventData& b) noexcept {
  using std::swap;
  swap(a.event_name, b.event_name);
  swap(a.wall_time, b.wall_time);
}

}  // namespace internal
}  // namespace fimsrg

#endif  // FIMSRG_UTILITY_PROFILING_INTERNAL_PROFILING_EVENT_DATA_H_
