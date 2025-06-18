// Copyright (C) 2025 The sdk authors. All rights reserved.
#include "crypto/hash.h"

#include <openssl/evp.h>

#include "absl/log/check.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"

namespace sdk {
namespace crypto {

absl::StatusOr<Hash*> Hash::New(const Hash::Options& options) {
  return nullptr;
}

Hash::~Hash() {
  //
}

absl::Status Hash::Update(const void* data, size_t len) {
	DCHECK(data != nullptr) << "the data pointer can't be null";
  return absl::OkStatus();
}

absl::Status Hash::Finalize() { return absl::OkStatus(); }

}  // namespace crypto
}  // namespace sdk
