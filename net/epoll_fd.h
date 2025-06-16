// Copyright (C) 2025 The sdk authors. All rights reserved.
#ifndef NET_EPOLL_FD_H_
#define NET_EPOLL_FD_H_

#include <sys/epoll.h>

// A lightweight RAII wrapper for epoll.

namespace sdk {
namespace net {

class EpollFd {
 public:
  // Construct. Can fail. Call IsValid() to see if the creation was successful.
  EpollFd();
  ~EpollFd();

  // Copy and assignment not allowed.
  EpollFd(const EpollFd&) = delete;
  EpollFd(EpollFd&&) = delete;
  EpollFd& operator=(const EpollFd&) = delete;
  EpollFd& operator=(EpollFd&&) = delete;

  // Return the underlying epoll descriptor.
  int fd() const;

  // Return 'true' if the descriptor is valid.
  bool IsValid() const;

  // Add a descriptor to the epoll set.
  int Add(int fd, struct epoll_event* ev);

  // Modify a descriptor that's already in the epoll set.
  int Modify(int fd, struct epoll_event* ev);

  // Delete a descriptor from the epoll set.
  int Delete(int fd);

  // Constant that can be used in Wait() to wait forever.
  const int kWaitForever = -1;
  // Wait for activity on one or more epoll descriptors.
  int Wait(struct epoll_event* events, int maxevents, int timeout_ms);

 private:
  int epfd_;
};

}  // namespace net
}  // namespace sdk

#endif  // NET_EPOLL_FD_H_
