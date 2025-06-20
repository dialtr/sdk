// Copyright (C) 2024 The kvg authors. All rights reserved.
#include <gtest/gtest.h>
#include "absl/status/statusor.h"
#include "base/buffer.h"
#include "crypto/hash.h"

using ::absl::StatusOr;
using ::sdk::base::Buffer;
using ::sdk::crypto::Hash;

TEST(NetTest, BasicAssertions) {
  StatusOr<Hash*> result = Hash::New(Hash::Options());
	
	const char data[] = {'1', '2', '3'};
	Hash* hash = result.value();
	hash->Update(data, 3);
		
  EXPECT_STRNE("hello", "world");
  EXPECT_EQ(7 * 6, 42);
}
