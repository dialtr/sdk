// Copyright (C) 2024 The kvg authors. All rights reserved.
#include "crypto/hash.h"

#include <gtest/gtest.h>

#include <iostream>
#include <string>

#include "absl/status/statusor.h"
#include "base/buffer.h"

using ::absl::StatusOr;
using ::sdk::base::Buffer;
using ::sdk::crypto::Hash;
using ::std::cerr;
using ::std::endl;

TEST(HashTest, Finalize) {
  StatusOr<Hash*> result = Hash::New(Hash::Options());
  const char data[] = {'t', 'e', 's', 't', '\n'};
  Hash* hash = result.value();
  hash->Update(data, 5);
  StatusOr<Buffer> hash_result = hash->Finalize();
  EXPECT_TRUE(hash_result.ok());
  const std::string hex = hash_result.value().ToHex();
  EXPECT_EQ("f2ca1bb6c7e907d06dafe4687e579fce76b37e4e93b7605022da52e6ccc26fd2",
            hex);
  delete (result.value());
}
