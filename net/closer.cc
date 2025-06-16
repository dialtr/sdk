// Copyright (C) 2025 The sdk authors. All rights reserved.
#include "net/closer.h"

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "net/net.h"

namespace sdk {
namespace net {

Closer::Closer(int fd) : fd_(fd), will_close_(true) {
  LOG_IF(WARNING, fd_ < 0)
      << "file descriptor '" << fd_
      << "' is not valid and no attempt to close it will be made";
}

Closer::~Closer() {
  if (will_close_ && (fd_ >= 0)) {
    Close(fd_);
  }
}

void Closer::Arm() { will_close_ = true; }

void Closer::Disable() { will_close_ = false; }

int Closer::fd() const { return fd_; }

bool Closer::will_close() const { return will_close_; }

}  // namespace net
}  // namespace sdk
