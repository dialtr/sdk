// Copyright (C) 2024 The kvg authors. All rights reserved.
#include <gtest/gtest.h>

TEST(NetTest, BasicAssertions) {
  EXPECT_STRNE("hello", "world");
  EXPECT_EQ(7 * 6, 42);
}
