// Copyright 2022 Matthias Heinz
#include "fimsrg/utility/checks/error.h"

#include <string_view>

#include "fimsrg/utility/checks/internal/error_eval.h"

namespace fimsrg {

void CheckForErrorState(bool error_state, std::string_view msg) {
  fimsrg::internal::CheckForError(error_state, msg);
}

void CheckValidationResult(const ValidationResult& validation_result) {
  fimsrg::internal::CheckForError(!validation_result.valid,
                                  validation_result.err_msg);
}

}  // namespace fimsrg
