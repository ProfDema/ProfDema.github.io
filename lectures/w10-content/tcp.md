### Human Communication

Human communication is governed by rules: vocabulary, sentence structure,
spelling, grammar...

How would you like it if a l   l th  elect ur e sli  des we r e 

fo r ma ttt  ed like thiiiiiis ?!.$

---

### Computer Communication
Computer communication is also governed by rules:
* *Encoding* of information, e.g., text, signed/unsigned
integers, floating point
* *Ordering* of bytes, e.g., big endian, little endian
* *Message sequencing*, e.g., first send username, then send password
* *Message start and end boundaries*, e.g., CRLF (`\r\n`)
to terminate messages

---

### Transport Protocols

Two widespread models of *transport protocols* for
computer communication over a network:

1. Connectionless: Exemplified by `UDP` protocol
2. Connection-oriented: Exemplified by `TCP` protocol

Protocols are a set of *rules*. 
Both TCP and UDP protocols are implemented by the *operating system*.

---

### CSC209 vs. CSC358

* In CSC209, we learn what is necessary to *use* TCP
to communicate over a network
  * No UDP, due to time constraints
* In CSC358, you will learn *how TCP and UDP work*

notes:
Just like how CSC209 involves *using* system calls,
and CSC369 involves how system calls work "under the hood"

---

### UDP

* UDP is used for sending a *datagram* from one machine to another
* A datagram is a self-contained message with a beginning
and end
* The OS sends the datagram, but doesn't
follow up to make sure that it got delivered

---

### TCP

* TCP is used to establish a *socket* (similar to a pipe)
to communicate between two processes
  * Processes may be on the same computer, or two different computers
  connected by a network
* The socket is created using a system call
* The process sending the data writes a sequence of bytes to the socket
* The OS guarantees that the bytes will be delivered over the network,
in the correct order, to the receiving process

---

### UDP vs. TCP

* Comparing UDP and TCP is like comparing SMS and WhatsApp
* If you send an SMS to your friend, you have no way of knowing if
they received your message
  * Perhaps they may reply back to you confirming that they received
  your message
* If you send a message over WhatsApp, **the app itself tells you whether
or not the message was successfully delivered**

---

### We were planning to tell a UDP joke on this slide...

![Bad joke eel](./w10-figs/eel.jpg)
<!-- .element class="stretch" -->

### But we weren't sure if you would get it.

---

### Internet Protocol (IP) Addresses

* An *IP address* identifies a specific host (computer) on a specific network.
* IPv4 addressing (most widespread) identifies hosts by
four decimal 8-bit integers separated by dots, e.g., `128.100.3.30`
* IPv6 addressing ([slowly being adopted](https://www.google.com/intl/en/ipv6/statistics.html))
identifies hosts by eight groups of four hexadecimal digits, separated by colons,
e.g., `fe80:1234:0432:a2d8:61ff:fe8b:8924:c23f`

---

### TCP and UDP Ports

* An IP address only identifies a host, but not which program running on the host
* To communicate with a specific program on a host, you must
specify a *port number* between `0` and `65535`
* For Tutorial 10/11 and Assignment 4, your client and server programs must
use the same port number; otherwise, they cannot communicate

---

### Port Number Conventions

* Ports in range `0-1023` are *well-known* or *reserved*
(e.g., `22` for SSH, `80` for HTTP, `443` for HTTPS)
* Ports in range `1024-49151` are *registered*
(e.g., `3724` for World of Warcraft)
* Ports in range `49152-65535` are *dynamic*
  * These are the ones you should typically pick, to avoid conflict

[See IANA for list of port assignments](https://www.iana.org/assignments/service-names-port-numbers/service-names-port-numbers.txt)

---

### `localhost`

* You may test your client and server programs by running both on the same computer
* `127.0.0.1` is the "loopback" IP address, for when your program
needs to communicate with another program on the same computer
* `localhost` is a *hostname* "aliased" to `127.0.0.1`
* To test your client and server on different PCs,
obtain the PC's IP address by running `ifconfig`
  * Lab PCs have IP address in the range `142.1.X.Y`

---

![](./w10-figs/home.jpg)
<!-- .element class="stretch" -->

