// Copyright 2022 Matthias Heinz
#include "fimsrg/utility/profiling/internal/profiling_database.h"

#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

#include "absl/container/flat_hash_map.h"

// PRIVATE
#include "fmt/core.h"

#include "fimsrg/utility/profiling/internal/profiling_data.h"
#include "fimsrg/utility/profiling/internal/profiling_event_data.h"

// PRIVATE
#include "fimsrg/utility/checks/error.h"

namespace fimsrg {
namespace internal {

inline std::vector<ProfilingData> SortProfilingData(
    const absl::flat_hash_map<std::string, ProfilingData>& event_data) {
  std::vector<ProfilingData> events;
  events.reserve(event_data.size());

  for (const auto& i : event_data) {
    events.push_back(i.second);
  }

  std::sort(events.begin(), events.end());

  return events;
}

inline std::string GetProfileReportHeader() {
  return fmt::format("{:50} {:11} {:11} {:11}\n", "EVENT NAME", "NUM EVENTS",
                     "WALLTIME(s)", "PER CALL(s)");
}

inline std::string GetProfileReportString(const ProfilingData& data) {
  double per_call = 0.0;
  if (data.event_count > 0) {
    per_call = data.wall_time / data.event_count;
  }
  return fmt::format("{:50} {:11} {:11.6} {:11.6}\n", data.event_name,
                     data.event_count, data.wall_time, per_call);
}

ProfilingDatabase& ProfilingDatabase::GetInstance() {
  static ProfilingDatabase instance;
  return instance;
}

void ProfilingDatabase::AddProfilingEvent(
    const ProfilingEventData& event_data) {
  event_data_[event_data.event_name].AddProfilingEvent(event_data);
}

void ProfilingDatabase::WriteProfileReport(std::string path_to_file) const {
  const auto entries = GenerateProfileReportEntries();

  std::ofstream file(path_to_file);
  fimsrg::CheckForError(
      !file.is_open(),
      ErrorMessage(
          fmt::format("Failed to open profile report file at {}", path_to_file)
              .c_str()));

  file << GetProfileReportHeader() << "\n";
  for (const auto& entry : entries) {
    file << entry << "\n";
  }
}

std::vector<std::string> ProfilingDatabase::GenerateProfileReportEntries()
    const {
  const auto sorted_data = SortProfilingData(event_data_);
  std::vector<std::string> entries;
  entries.reserve(sorted_data.size());

  for (auto it = sorted_data.rbegin(); it != sorted_data.rend(); ++it) {
    entries.push_back(GetProfileReportString(*it));
  }

  return entries;
}

std::string ProfilingDatabase::GetProfileReportHeader() const {
  return GetProfileReportHeader();
}

ProfilingDatabase::ProfilingDatabase() {}

ProfilingDatabase::~ProfilingDatabase() {}

}  // namespace internal
}  // namespace fimsrg
