// Copyright (C) 2025 The sdk authors. All rights reserved.
#ifndef NET_CLOSER_H_
#define NET_CLOSER_H_

// RAII wrapper that automatically closes a file on scope exit unless the
// caller calls Disable().
// Note: this class calls net::Close(), which logs if close() fails.

namespace sdk {
namespace net {

class Closer {
 public:
  explicit Closer(int fd);
  ~Closer();

  // Copy, assignment not allowed.
  Closer(const Closer&) = delete;
  Closer(Closer&&) = delete;
  Closer& operator=(const Closer&) = delete;
  Closer& operator=(Closer&&) = delete;

  // Arm the Closer to close the file on scope exit. Note that this is the
  // default situation: the user does not need to call Arm() unless they
  // wish to revert a prior call to Dismiss().
  void Arm();

  // Disable the automatic close, meaning that the file will NOT be closed
  // on scope exit. This is normally done when a number of potentially
  // failing operations have succeeded and the caller wishes to return the
  // contained descriptor.
  void Disable();

  // Access the contained file descriptor.
  int fd() const;

  // Return 'true' if the file will be closed on scope exit. This is the
  // default case when constructed. Returns false if cleanup has been
  // disabled via a call to Disable();
  bool will_close() const;

 private:
  int fd_;
  bool will_close_;
};

}  // namespace net
}  // namespace sdk

#endif  // NET_CLOSER_H_
