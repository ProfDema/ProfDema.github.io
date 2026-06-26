### Pipes: Unidirectional vs. Bidirectional Communication

![](./w10-figs/pipes.svg)

---

### Sockets

![](./w10-figs/sockets.svg)

* A server must have a *listener socket* to accept new connections
* A separate socket is created to communicate with each client

---

### System Calls for Setting up a Server

1. `socket`: Creates a socket.
2. `bind`: Assigns an address and port to the socket. (must
assign an IP address that actually belongs to your systems).
3. `listen`: Establish a queue for incoming connections.
4. `accept`: Accept queued incoming connection and create a new socket.
5. `read`/`write`: Receive/send data on socket.

---

### System Calls for Setting up a Client

1. `socket`: Creates a socket
2. `connect`: Connects to a remote server using IP address
and port.
3. `read`/`write`: Receive/send data on socket.

---

![](./w10-figs/socket_syscalls.svg)
<!-- .element class="stretch" -->

---

### IP Address Struct

* System calls expect the IP address to be passed in as an
`in_addr` struct
* Use `inet_aton` to convert IP addres from a string
in the form `a.b.c.d` into an `in_addr` struct
* Use `inet_ntoa` to convert `in_addr` struct into
string in the form `a.b.c.d`

---

### Endianness

* By convention, all data being sent over the network must first be
converted into *big endian*, known as *network byte order*
* The endianness of the host is referred to as *host byte order*
* `htonl()`, `htons()`, `ntohl()`, and `ntohs()` are used for
converting between *host byte order* and *network byte order*
  * See man pages for usage
  * Even port numbers must be converted
  * ASCII text does not require conversion (why?)

---

## Sockets Worksheet
