// Copyright (C) 2025 The sdk authors. All rights reserved.
#include "crypto/hash.h"

#include <openssl/evp.h>

#include <iostream>

#include "absl/log/check.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"

namespace {

const size_t kSha256Size = 32;

}  // namespace

namespace sdk {
namespace crypto {

using sdk::base::Buffer;

class HashImpl : public Hash {
 public:
  HashImpl(const Hash::Options& options) : options_(options), ctx_(nullptr) {}

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
    if (status == 0) {
      return absl::UnknownError("failed to initialize digest object");
    }

    ctx_ = ctx;

    return absl::OkStatus();
  }

  // Update the hash with new data.
  bool Update(const void* data, size_t len) override {
    DCHECK(ctx_ != nullptr);
    const int status = EVP_DigestUpdate(ctx_, data, len);
    return (status == 1);
  }

  // Finish the hashing operation. Updates are no longer possible.
  absl::StatusOr<sdk::base::Buffer> Finalize() override {
    Buffer ret(kSha256Size);
    const int status = EVP_DigestFinal_ex(
        ctx_, reinterpret_cast<unsigned char*>(ret.Data()), nullptr);
    if (status == 0) {
      return absl::InternalError("failed to finalize hash object");
    }
    return std::move(ret);
  }

  // Destroty the hash.
  ~HashImpl() override {
    DCHECK(ctx_ != nullptr);
    EVP_MD_CTX_free(ctx_);
  }

 private:
  Hash::Options options_;
  EVP_MD_CTX* ctx_;
};

absl::StatusOr<Hash*> Hash::New(const Hash::Options& options) {
  HashImpl* hash = new HashImpl(options);
  const absl::Status status = hash->Initialize();
  if (status.ok()) {
    return hash;
  }
  delete hash;
  return status;
}

}  // namespace crypto
}  // namespace sdk
