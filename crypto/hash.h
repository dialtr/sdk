// Copyright (C) 2025 The sdk authors. All rights reserved.
#ifndef CRYPTO_HASH_H_
#define CRYPTO_HASH_H_

#include "absl/status/status.h"
#include "absl/status/statusor.h"

#include "base/buffer.h"

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

	// Update the hash with new data.
  virtual int Update(const void* data, size_t len) = 0;

  // Finish the hashing operation. Updates are no longer possible.
  virtual absl::StatusOr<sdk::base::Buffer> Finalize() = 0;

  // Destroty the hash.
  virtual ~Hash() = 0;
};

}  // namespace crypto
}  // namespace sdk

#endif  // CRYPTO_HASH_H_
