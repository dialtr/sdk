// Copyright (C) 2025 The sdk authors. All rights reserved.
#ifndef CRYPTO_HASH_H_
#define CRYPTO_HASH_H_

#include "absl/status/status.h"
#include "absl/status/statusor.h"

namespace sdk {
namespace crypto {

class Hash {
 public:
  enum class Algorithm { kSha256 = 0 };

  struct Options {
    Algorithm algorithm = Algorithm::kSha256;
  };

  // Create a new Hash object with the specified options.
  static absl::StatusOr<Hash*> New(const Hash::Options& options);

  // Destroty the hash.
  ~Hash();

  // No default ctor; copy / assignment not allowed.
  Hash() = delete;
  Hash(const Hash&) = delete;
  Hash& operator=(const Hash&) = delete;

  // TODO(tdial): Implement move constructor?
  // TODO(tdial): Implement move assignment?

  // Update the hash with new data.
  absl::Status Update(const void* data, size_t len);

  // Finish the hashing operation. Updates are no longer possible.
  absl::Status Finalize();

 private:
};

}  // namespace crypto
}  // namespace sdk

#endif  // CRYPTO_HASH_H_
