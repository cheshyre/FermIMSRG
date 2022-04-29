// Copyright 2022 Matthias Heinz
#include "fimsrg/utility/profiling/internal/profiling_data.h"

// PUBLIC
#include "fimsrg/utility/profiling/internal/profiling_event_data.h"

// PRIVATE
#include "fimsrg/utility/checks/assert.h"

namespace fimsrg {
namespace internal {

void ProfilingData::AddProfilingEvent(const ProfilingEventData& event_data) {
  if (this->event_name != "") {
    Expects(this->event_name == event_data.event_name);
  } else {
    this->event_name = event_data.event_name;
  }
  this->event_count += 1;
  this->wall_time += event_data.wall_time;
}

}  // namespace internal
}  // namespace fimsrg
