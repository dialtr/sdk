// Copyright (C) 2025 The sdk authors. All rights reserved.
#include "absl/log/log.h"
#include "net/net.h"

int main(int argc, char* argv[]) {
  // TODO(tdial): Disable SIGINT: We will handle this gracefully.
  // TODO(tdial): Disable SIGTERM: We will handle this gracefully.
  // TODO(tdial): Disable SIGHUP: We will (possibly) re-read configs.
  // TODO(tdial): Disable SIGPIPE: We want EPIPE instead from write().

  // TODO(tdial): Create poller.
  // TOOD(tdial): Add signalfd's to poller (SIGINT, SIGTERM, SIGHUP).

  // TODO(tdial): Bind a TCP listener, add to the poller.

  // TODO(tdial): Run poll loop.

  return 0;
}
