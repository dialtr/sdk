// Copyright (C) 2025 The sdk authors. All rights reserved.
#ifndef BASE_BUFFER_H_
#define BASE_BUFFER_H_

#include <string>
#include <vector>

namespace sdk {
namespace base {

class Buffer {
 public:
  // Construct empty.
  Buffer();

  // Construct with data.
  Buffer(const void* data, size_t count);

  // Copy
  Buffer(const Buffer&);

  // Move copy.
  Buffer(Buffer&&);

  // Assignment.
  Buffer& operator=(const Buffer&);

  // Move assignment.
  Buffer& operator=(Buffer&&);

  // Append data to the buffer.
  Buffer& Append(const void* data, size_t count);

  // Append a byte.
  Buffer& Append(unsigned char byte);

  // Return a pointer to the data.
  const void* Data() const;

  // Return the size of the data.
  size_t Size() const;

  // Return a hex string of the data.
  std::string ToHex() const;

 private:
  std::vector<unsigned char> data_;
};

// Return a hex string of data.
std::string ToHex(const void* data, size_t size);

}  // namespace base
}  // namespace sdk

#endif  // BASE_BUFFER_H_
