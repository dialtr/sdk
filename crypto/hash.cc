// Copyright (C) 2025 The sdk authors. All rights reserved.
#include "crypto/hash.h"

#include <openssl/evp.h>

#include "absl/log/check.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"

namespace sdk {
namespace crypto {

using sdk::base::Buffer;

class HashImpl : public Hash {
 public:
	HashImpl(const Hash::Options& options) : options_(options), ctx_(nullptr) {
	}

	absl::Status Initialize() {
		if (options_.algorithm != Algorithm::kSha256) {
			return absl::InvalidArgumentError("algorithm not supported");
		}
		
		EVP_MD_CTX* ctx = EVP_MD_CTX_new();
		if (ctx == nullptr) {
			return absl::ResourceExhaustedError(
					"EVP_MD_CTX_new(): failed to allocate context");
		}

		const int status = EVP_DigestInit_ex(ctx, EVP_sha256(), nullptr);
		if (status != 0) {
			return absl::UnknownError("failed to initialize digest object");
		}

		return absl::OkStatus();
	}

	// Update the hash with new data.
  absl::Status Update(const void* data, size_t len) override {
		return absl::OkStatus();
	}

  // Finish the hashing operation. Updates are no longer possible.
  absl::StatusOr<sdk::base::Buffer> Finalize() override {
		Buffer ret;
		return std::move(ret);
	}

  // Destroty the hash.
  ~HashImpl() override {
	}

 private:
	Hash::Options options_;
	EVP_MD_CTX* ctx_;
};

absl::StatusOr<Hash*> Hash::New(const Hash::Options& options) {
	Hash* hash = nullptr;
  return hash;	
}

}  // namespace crypto
}  // namespace sdk
