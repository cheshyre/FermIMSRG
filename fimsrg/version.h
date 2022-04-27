// Copyright 2022 Matthias Heinz
#ifndef FIMSRG_VERSION_H_
#define FIMSRG_VERSION_H_

#include <string>

namespace fimsrg {

namespace internal {

// FermIMSRG major version.
constexpr int kFIMSRGMajorVersion = 0;
// FermIMSRG minor version.
constexpr int kFIMSRGMinorVersion = 1;
// FermIMSRG patch version.
constexpr int kFIMSRGPatchVersion = 0;

}  // namespace internal

// Get major version number of FermIMSRG.
inline int MajorVersion() { return ::fimsrg::internal::kFIMSRGMajorVersion; }

// Get minor version number of FermIMSRG.
inline int MinorVersion() { return ::fimsrg::internal::kFIMSRGMinorVersion; }

// Get patch version number of FermIMSRG.
inline int PatchVersion() { return ::fimsrg::internal::kFIMSRGPatchVersion; }

// Get version number string of FermIMSRG.
std::string VersionString();

}  // namespace fimsrg

#endif  // FIMSRG_VERSION_H_
