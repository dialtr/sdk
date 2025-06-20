// Copyright (C) 2024 The kvg authors. All rights reserved.
#include "base/buffer.h"

#include <gtest/gtest.h>

#include <iostream>
#include <string>

using ::sdk::base::Buffer;

TEST(BufferTest, DefaultConstruction) {
  Buffer b;
  EXPECT_EQ(0, b.Size());
}

TEST(BufferTest, DataConstruction) {
  char data[4] = {'a', 'b', 'c', 'd'};
  Buffer b(data, 4);
  EXPECT_EQ(4, b.Size());
}

TEST(BufferTest, CopyConstruction) {
  char data[4] = {'a', 'b', 'c', 'd'};
  Buffer orig(data, 4);
  EXPECT_EQ(4, orig.Size());

  Buffer copy(orig);
  EXPECT_EQ(4, copy.Size());

  const char* orig_ptr = reinterpret_cast<const char*>(orig.Data());
  const char* copy_ptr = reinterpret_cast<const char*>(copy.Data());
  for (int i = 0; i < 4; ++i) {
    EXPECT_EQ(orig_ptr[i], copy_ptr[i]);
  }
}

TEST(BufferTest, MoveConstruction) {
  char data[4] = {'a', 'b', 'c', 'd'};
  Buffer orig(data, 4);
  EXPECT_EQ(4, orig.Size());

  Buffer copy(std::move(orig));
  EXPECT_EQ(4, copy.Size());

  const char* copy_ptr = reinterpret_cast<const char*>(copy.Data());
  for (int i = 0; i < 4; ++i) {
    EXPECT_EQ(data[i], copy_ptr[i]);
  }
}

TEST(BufferTest, Assignment) {
  char data[4] = {'a', 'b', 'c', 'd'};
  Buffer orig(data, 4);
  EXPECT_EQ(4, orig.Size());

  Buffer copy;

  copy = orig;

  EXPECT_EQ(orig.Size(), copy.Size());
  const char* orig_ptr = reinterpret_cast<const char*>(orig.Data());
  const char* copy_ptr = reinterpret_cast<const char*>(copy.Data());
  for (int i = 0; i < 4; ++i) {
    EXPECT_EQ(orig_ptr[i], copy_ptr[i]);
  }
}

TEST(BufferTest, MoveAssignment) {
  char data[4] = {'a', 'b', 'c', 'd'};
  Buffer orig(data, 4);
  EXPECT_EQ(4, orig.Size());

  Buffer copy;

  copy = std::move(orig);

  EXPECT_EQ(4, copy.Size());
  const char* copy_ptr = reinterpret_cast<const char*>(copy.Data());
  for (int i = 0; i < 4; ++i) {
    EXPECT_EQ(data[i], copy_ptr[i]);
  }
}

TEST(BufferTest, ToHex) {
  Buffer a;
  a.Append(0x00);
  a.Append(0x10);
  a.Append(0x0f);
  std::string hex = a.ToHex();
  std::cout << hex << std::endl;
  EXPECT_EQ("00100F", hex);
}
