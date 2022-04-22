// Copyright 2022 Matthias Heinz
#ifndef FIMSRG_UTILITY_PROFILING_INTERNAL_PROFILING_DATABASE_H_
#define FIMSRG_UTILITY_PROFILING_INTERNAL_PROFILING_DATABASE_H_

#include <string>
#include <vector>

#include "absl/container/flat_hash_map.h"

#include "fimsrg/utility/profiling/internal/profiling_data.h"
#include "fimsrg/utility/profiling/internal/profiling_event_data.h"

namespace fimsrg {
namespace internal {

// Singleton class to contain full set of profiling data.
class ProfilingDatabase {
 public:
  // Get database singleton instance.
  static ProfilingDatabase& GetInstance();

  // Database is a singleton.
  ProfilingDatabase(const ProfilingDatabase&) = delete;

  // Database is a singleton.
  ProfilingDatabase& operator=(const ProfilingDatabase&) = delete;

  // Add data for an event into the database.
  void AddProfilingEvent(const ProfilingEventData& event_data);

  // Write profile report to a specified file.
  void WriteProfileReport(std::string path_to_file) const;

  // Get a vector of profile report strings (sorted by decreasing cost).
  std::vector<std::string> GenerateProfileReportEntries() const;

  // Get a header for the profiling report.
  std::string GetProfileReportHeader() const;

 private:
  absl::flat_hash_map<std::string, ProfilingData> event_data_;

  // Private constructor.
  ProfilingDatabase();

  // Private destructor.
  ~ProfilingDatabase();
};
}  // namespace internal
}  // namespace fimsrg

#endif  // FIMSRG_UTILITY_PROFILING_INTERNAL_PROFILING_DATABASE_H_
