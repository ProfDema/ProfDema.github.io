## Extra Slides 

---

### Defining Message Boundaries
 
* Assume that a sender sends the sequence of bytes "Hello world" 
to a receiver over a TCP socket
* TCP guarantees that the receiver will receive the entire sequence,
eventually
* But it's possible that when the receiver calls `read()` on the socket:
  * The entire message wasn't received yet
  * The `read()` call was interrupted (e.g., see `EINTR` in `man 2 read`)

---

### Question
How do we know when we have received a complete message, and not a partial message?

### Answer
We define a byte sequence that indicates the end of a message. In text-based
protocols, the most common convention is to signify an end-of-message with a CRLF
(carriage-return + newline, or `\r\n`) sequence. Actual message content
must not contain any instances of this sequence.

---

### Question

Are there alternative techniques for determining that we have reached a complete message?

### Answer

Yes. Two common techniques:

1. Define a fixed-length message format (i.e., every message must be identical in length).
2. Define a fixed-length "header" that contains an integer representing the length
of the remainder of the message.

---

### Question

It is possible for the server (or client) to call `read()` on a socket and receive
more than one message?

### Answer

Yes. This might happen if the sender is sending the messages
faster you are reading them. In this case, you must save the messages
in a *buffer* and handle them one message at a time.

---

### Buffering

* Buffering is an extremely common technique, especially in networking.
* In addition to the buffering that you are implementing in tutorial 10,
note that the Operating System also does its own buffering
* What happens if your PC receives data from the network, but your program
isn't ready to call `read()` yet, because it is busy doing something else?
  * Answer: The OS saves it in a buffer, until your program calls `read()`

---

### The TCP/IP Model

![](./w10-figs/tcpip.svg)
<!-- .element class="stretch" -->

---

### Application Layer

In this course, when we define a message format, what we are really doing
is defining an *application-layer protocol* that governs how our server
and client communicate with each other

---

### Transport Layer

*Transport protocols*, such as TCP and UDP, govern how your OS
"packages up" your application data to send it to another host over
the network, and check to make sure that it arrived at the destination.

---

### Internet Layer

*Internet protocols* such as IP, RIP, and OSPF govern how your data gets
transferred from one Internet Service Provider (ISP; e.g., Bell, Rogers)
to another

---

### Link Layer

*Link-layer protocols* deal with how your device physically transmits
the data, e.g., wirelessly, or over a copper or fibre-optic cable

---

### Remark about Layering

Layering is done for a good reason: Imagine, when writing your chat
server/client for Tutorial 11, that you had to write separate code
based on whether your client is connected over a WiFi connection or
an Ethernet cable!

---

### TCP: Additional Features

* TCP has many more features that are beyond the scope of our
discussions for this course
* Flow control: If a computer is sending data too fast for the
receiver to handle, TCP will automatically slow down to avoid
data loss
* Congestion control: If the network is too congested, TCP
will automatically slow down to avoid data loss
