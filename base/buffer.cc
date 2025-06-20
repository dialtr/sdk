// Copyright (C) 2025 The sdk authors. All rights reserved.
#include "base/buffer.h"

#include <string.h>

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

#include "absl/log/check.h"

namespace sdk {
namespace base {

Buffer::Buffer() {}

Buffer::Buffer(const void* data, size_t count) {
  DCHECK(data != nullptr);
  data_.resize(count);
  memcpy(&data_[0], data, count);
}

Buffer::Buffer(const Buffer& copy) : data_(copy.data_) {}

Buffer::Buffer(Buffer&& copy) : data_(std::move(copy.data_)) {}

Buffer& Buffer::operator=(const Buffer& other) {
  std::vector<unsigned char> tmp(other.data_);
  std::swap(this->data_, tmp);
  return *this;
}

Buffer& Buffer::operator=(Buffer&& other) {
  std::vector<unsigned char> tmp(std::move(other.data_));
  std::swap(tmp, this->data_);
  return *this;
}

Buffer& Buffer::Append(const void* data, size_t count) {
  DCHECK(data != nullptr);
  const size_t prev_size = data_.size();
  data_.resize(prev_size + count);
  memcpy(&(data_[prev_size]), data, count);
  return *this;
}

Buffer& Buffer::Append(unsigned char byte) {
  data_.push_back(byte);
  return *this;
}

const void* Buffer::Data() const {
  const unsigned char* const data = &data_[0];
  return reinterpret_cast<const void*>(data);
}

size_t Buffer::Size() const { return data_.size(); }

std::string Buffer::ToHex() const { return sdk::base::ToHex(Data(), Size()); }

std::string ToHex(const void* data, size_t size) {
  static const char table[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                               '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
  DCHECK(data);
  const unsigned char* p = reinterpret_cast<const unsigned char*>(data);
  std::stringstream ss;
  for (size_t i = 0; i < size; ++i) {
    const unsigned char ch = p[i];
    ss << table[(ch >> 4) & 0xf];
    ss << table[ch & 0xf];
  }
  return ss.str();
}

}  // namespace base
}  // namespace sdk
