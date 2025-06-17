// Copyright (C) 2025 The sdk authors. All rights reserved.
#ifndef NET_NET_H_
#define NET_NET_H_

#include <stddef.h>
#include <sys/socket.h>

namespace sdk {
namespace net {

// Wrapper around close.
int Close(int sock);

// Create a TCP socket with the specified options.
int CreateTcpSocket(bool blocking);

// Create a UDP socket with the specified options.
int CreateUdpSocket(bool blocking);

// Configure socket for address reuse (if true) or no reuse (if false.)
int SetAddressReuse(int sock, bool reuse);

// Configure socket for blocking (if true) or nonblocking (if false.)
int SetBlockingMode(int sock, bool blocking);

// Wraper around accept(). Handles EINTR.
int Accept(int sockfd, struct sockaddr* addr, socklen_t* addrlen);

// Wrapper around listen().
int Listen(int sock, int backlog);

// Wrapper around read(). Read at most 'size' bytes. Handles EINTR.
int Read(int fd, void* buf, size_t size);

// Wrapper around write(). Write at most 'size' bytes. Handles EINTR.
int Write(int fd, void* buf, size_t size);

}  // namespace net
}  // namespace sdk

#endif  // NET_NET_H_
