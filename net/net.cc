// Copyright (C) 2025 The sdk authors. All rights reserved.
#include "net/net.h"

#include <arpa/inet.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "net/closer.h"

namespace sdk {
namespace net {

int Close(int sock) {
  DCHECK_GE(sock, 0);
  const int status = close(sock);
  PLOG_IF(ERROR, status != 0) << "close() failed for socket " << sock;
  return status;
}

int InternalCreateSocket(int family, int type, int protocol, bool blocking) {
  const int sock = socket(family, type, protocol);
  PLOG_IF(ERROR, sock < 0) << "socket() failed";
  if (sock < 0) {
    return sock;
  }
  // By default, sockets are created in blocking mode. As an optimization, do
  // not call SetBlockingMode() unless the caller requests a nonblocking fd.
  if (!blocking) {
    Closer closer(sock);
    const int status = SetBlockingMode(sock, blocking);
    if (status != 0) {
      return status;
    }
    closer.Disable();
  }
  return sock;
}

int CreateTcpSocket(bool blocking) {
  return InternalCreateSocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, blocking);
}

int CreateUdpSocket(bool blocking) {
  return InternalCreateSocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, blocking);
}

int SetAddressReuse(int sock, bool reuse) {
  DCHECK_GE(sock, 0);
  const int reuse_addr = reuse ? 1 : 0;
  const int status =
      setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof(int));
  PLOG_IF(ERROR, status != 0)
      << "setsockopt() failed to set address reuse for socket " << sock;
  return status;
}

int SetBlockingMode(int sock, bool blocking) {
  DCHECK_GE(sock, 0);
  const int flags = fcntl(sock, F_GETFL);
  PLOG_IF(ERROR, flags < 0) << "fcntl() failed to get flags";
  if (flags < 0) {
    return flags;
  }
  const int newflags =
      blocking ? (flags & (~O_NONBLOCK)) : (flags | O_NONBLOCK);
  const int status = fcntl(sock, F_SETFL, newflags);
  PLOG_IF(ERROR, status != 0) << "fcntl() failed to set flags";
  return status;
}

int Listen(int sock, int backlog) {
  DCHECK_GE(sock, 0);
  DCHECK_GE(backlog, 0);
  const int status = listen(sock, backlog);
  PLOG_IF(ERROR, status != 0) << "listen() failed";
  return status;
}

}  // namespace net
}  // namespace sdk
