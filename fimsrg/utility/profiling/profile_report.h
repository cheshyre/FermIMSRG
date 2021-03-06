// Copyright 2022 Matthias Heinz
#ifndef FIMSRG_UTILITY_PROFILING_PROFILE_REPORT_H_
#define FIMSRG_UTILITY_PROFILING_PROFILE_REPORT_H_

#include <string>
#include <vector>

namespace fimsrg {

// Write a profile report to the file provided.
void WriteProfileReportToFile(std::string path_to_file);

// Get a vector of sorted (most to least expensive) entries.
std::vector<std::string> GetProfileReportEntries();

// Get the header of a profile report.
std::string GetProfileReportHeader();

}  // namespace fimsrg

#endif  // FIMSRG_UTILITY_PROFILING_PROFILE_REPORT_H_
