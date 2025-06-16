// Copyright (C) 2025 The sdk authors. All rights reserved.
#ifndef NET_NET_H_
#define NET_NET_H_

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

// Wrapper around standard listen.
int Listen(int sock, int backlog);

}  // namespace net
}  // namespace sdk

#endif  // NET_NET_H_
