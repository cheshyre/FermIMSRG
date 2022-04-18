// Copyright 2022 Matthias Heinz
#include "fimsrg/utility/profiling/internal/profiling_database.h"

#include <string>

#include "absl/container/flat_hash_map.h"

#include "fimsrg/utility/profiling/internal/profiling_event_data.h"

namespace fimsrg {
namespace internal {

ProfilingDatabase& ProfilingDatabase::GetInstance() {
  static ProfilingDatabase instance;
  return instance;
}

void ProfilingDatabase::AddProfilingEvent(
    const ProfilingEventData& event_data) {
  event_data_[event_data.event_name].AddProfilingEvent(event_data);
}

void ProfilingDatabase::WriteProfileReport(std::string path_to_file) const {
  (void)path_to_file;
  // TODO(mheinz): implement
}

ProfilingDatabase::ProfilingDatabase() {}

ProfilingDatabase::~ProfilingDatabase() {}

}  // namespace internal
}  // namespace fimsrg
