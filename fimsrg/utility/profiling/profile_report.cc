// Copyright 2022 Matthias Heinz
#include "fimsrg/utility/profiling/profile_report.h"

#include <string>

// PRIVATE
#include "fimsrg/utility/profiling/internal/profiling_database.h"

namespace fimsrg {

void WriteProfileReportToFile(std::string path_to_file) {
  const auto& prof_db = fimsrg::internal::ProfilingDatabase::GetInstance();
  prof_db.WriteProfileReport(path_to_file);
}

std::vector<std::string> GetProfileReportEntries() {
  const auto& prof_db = fimsrg::internal::ProfilingDatabase::GetInstance();
  return prof_db.GenerateProfileReportEntries();
}

std::string GetProfileReportHeader() {
  const auto& prof_db = fimsrg::internal::ProfilingDatabase::GetInstance();
  return prof_db.GetProfileReportHeader();
}

}  // namespace fimsrg
