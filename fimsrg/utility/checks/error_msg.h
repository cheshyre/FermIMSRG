// Copyright 2022 Matthias Heinz
#ifndef FIMSRG_UTILITY_CHECKS_ERROR_MSG_H_
#define FIMSRG_UTILITY_CHECKS_ERROR_MSG_H_

#include "fimsrg/utility/checks/internal/error_eval.h"

#define ErrorMessage(x) \
  fimsrg::internal::GenerateFullErrorMessage(__FILE__, __LINE__, x)

#endif  // FIMSRG_UTILITY_CHECKS_ERROR_MSG_H_
