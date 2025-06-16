# proxy

## About

A simple TCP proxy, written for educational purposes.


## Design Notes

At a high level, **proxy** will implement a simple TCP proxy server that
listens on a particular port for new TCP connections and proxies them to
another server. The general workflow will be something like this:

1. Accept a connection from a listener bounder on TCP interface/port. We shall
   call this connection the **source** socket.
2. Initiate a connection to the target. We shall call this connection the
   **destination** socket.
3. Once the connection is established, proxy data in both directions
   between the source and destination sockets.
4. If at any point, either the source or destination connections are closed,
   the other side will be closed as well. Likewise, there will be a
   configurable inactivity period (possibly infinite) after which the
   proxy connection will be torn down.

The server will pass the bytes as-is, with no modification.


## Implementation Notes

We shall call a pair of sockets involved in a proxy setup to be called a
**proxy context**. The proxy context shall hold the descriptors involved in
a given proxy connection, along with any resources (such as buffers) and/or
counters, timers, and anything else necessary to track the proxy. The proxy
context object owns these resources: other objects may *reference* the proxy
context.

An example of an object that *references* the proxy context are structures
associated with the individual descriptors and timers. These are distinct
objects, since they are separately associated to actual descriptors that are
members of the set of descriptors monitored by the poller. Having separate
structures for the descriptor allows for per-descriptor state (otherwise not
relevant to the proxy context) to be stored separately. An example of this
type of state would be information related to the state of the descriptor
in the poll set.

The proxy is implemented in an event-driven style that minimizes thread
context switches (AKA thread hops) in the interest of improving performance.
Once initial setup takes place, the program shall enter an event loop in which
the main thread blocks in a call to epoll_wait(), processing dequeued events
to drive progress of proxied connections. The types of events that can be
returned by the epoll wait operation are:

1. A descriptor is ready for more data to be read or written.
2. A signal has been delivered to the process (we set a **signalfd**
   descriptor for the signals we are interested in receiving.)
3. A timeout has occurred. The proxy server will maintain a list of timers in
   order of their absolute expiration time, and a signal **timerfd** will be
   used to track when the next expiration should occur. (Note: this implies
   a timer module capable of managing a timer set.


## Reminder of things that can happen on sockets.

1. When calling **accept()**.
  a. The accept() call returns a socket >= 0 if successful.
  b. The accept() call returns -1 on a failure. Reasons include:
  c. Calling accept() on a nonblocking socket could return -1 and the
     errno could be EAGAIN / EWOULDBLOCK. Since we will always be operating
     on the listener after it returns an event from epoll() we should log
     this as an error but continue to try again.
  d. Like most syscalls, accept() could return EINTR, which can happen if
     a signal is delivered to the process. We should just try again. We may
     not even log this condition as it is normal.
  e. Any other error is a legitimate error which should be logged, but we
     can try again.

2. When calling **connect()**.
  a. The connect() call can return a socket >= 0 if successful.
  b. The connect() call returns -1 on failure. Reasons include:
  c. The errno is EINTR, in which case the operation can be retried.
  d. The errno is EINPROGRESS, in which case the socket was a nonblocking
     socket, and the connection started but was not completed yet. If this
     happens, the descriptor should be added to the epoller so that we are
     notified of write readiness.  When the epoll loop tells us that the 
     socket is writable, we should call getsockopt() to retrieve the socket
     error to determine what happened.
  e. Any other error is a connection error that may be temporary, so it 
     should be logged and any othe resources related to the connection
     should be freed.

3. When calling **read()**.
  a. The read() call can return 0, which means the peer has closed the
     connection.
  b. The read() call can return the number of bytes it has read (a positive
     number greater than 0). This is considered, of course, a success.
  c. The read() call can return -1. Reasons include:
  d. The error is EINTR, in which the operation can be retried.
  e. The error is EAGAIN / EWOULDBLOCK. Since we will always be operating
     on sockets after a return from an epoll_wait operation returns an event,
     this is unlikely. We should log this error and continue again.
  f. Any other error indicates an error that can't be recovered from.
 
4. When calling **write()**.
  a. The write() call can return the number of bytes written, a positive
     number greater than zero (Assuming we never call write with zero bytes.
  b. The write() call can return -1 on failure. Reasons include:
  c. The errno is EINTR, which indicates the operation can be restarted.
  d. The errno is EPIPE, which signals that the peer has closed the other
     side of the connection. This indicates an error that can't be recovered,
     and the correct action is to tear down the socket.


