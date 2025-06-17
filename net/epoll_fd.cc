// Copyright (C) 2025 The sdk authors. All rights reserved.
#include "net/epoll_fd.h"

#include <errno.h>
#include <sys/epoll.h>
#include <unistd.h>

#include "absl/log/check.h"
#include "absl/log/log.h"

namespace sdk {
namespace net {

EpollFd::EpollFd() : epfd_(-1) { epfd_ = epoll_create1(EPOLL_CLOEXEC); }

EpollFd::~EpollFd() {
  const int status = close(epfd_);
  PLOG_IF(WARNING, status != 0) << "close() failed";
}

int EpollFd::fd() const { return epfd_; }

bool EpollFd::IsValid() const { return (epfd_ >= 0); }

int EpollFd::Add(int fd, struct epoll_event* ev) {
  DCHECK_GE(epfd_, 0);
  DCHECK_GE(fd, 0);
  DCHECK_NE(ev, nullptr);
  return epoll_ctl(epfd_, EPOLL_CTL_ADD, fd, ev);
}

int EpollFd::Modify(int fd, struct epoll_event* ev) {
  DCHECK_GE(epfd_, 0);
  DCHECK_GE(fd, 0);
  DCHECK_NE(ev, nullptr);
  return epoll_ctl(epfd_, EPOLL_CTL_MOD, fd, ev);
}

int EpollFd::Delete(int fd) {
  DCHECK_GE(epfd_, 0);
  DCHECK_GE(fd, 0);
  return epoll_ctl(epfd_, EPOLL_CTL_DEL, fd, nullptr);
}

int EpollFd::Wait(struct epoll_event* events, int maxevents, int timeout_ms) {
  DCHECK_GE(epfd_, 0);
  DCHECK_NE(events, nullptr);
  int status = 0;
  do {
    status = epoll_wait(epfd_, events, maxevents, timeout_ms);
  } while ((status == -1) && (errno == EINTR));
  return status;
}

}  // namespace net
}  // namespace sdk
