# ft_irc

An IRC server in C++ 98.

## Mandatory Part

### Program name

`ircserv`

### Turn in files

`Makefile`, `*.{h,hpp}`, `*.cpp`, `*.tpp`, `*.ipp`, and an optional configuration file.

### Makefile

`NAME`, `all`, `clean`, `fclean`, `re`

### Arguments

`port`: The listening port.

`password`: The connection password.

### External functs

Everything in C++ 98.

`socket`, `close`, `setsockopt`, `getsockname`, `getprotobyname`, `gethostbyname`, `getaddrinfo`, `freeaddrinfo`, `bind`, `connect`, `listen`, `accept`, `htons`, `htonl`, `ntohs`, `ntohl`, `inet_addr`, `inet_ntoa`, `send`, `recv`, `signal`, `lseek`, `fstat`, `fcntl`, `poll` (or equivalent).

### Libft

Not authorized.

### Description

You have to develop an IRC server in C++ 98. You mustn't develop a client. You mustn't handle server-to-server communication.

Your executable will be run as follows:

`./ircserv <port> <password>`

* `port`: The port number on which your IRC server will be listening to for incoming IRC connections.
* `password`: The connection password. It will be needed by any IRC client that tries to connect to your server.

Even if `poll()` is mentioned in the subject and the evaluation scale, you can use any equivalent such as `select()`, `kqueue()`, or `epoll()`.

#### Requirements

* The server must be capable of handling multiple clients at the same time and never hang.
* Forking is not allowed. All I/O operations must be non-blocking.
* Only 1 `poll()` (or equivalent) can be used for handling all these operations (read, write, but also listen, and so forth).

Because you have to use non-blocking file descriptors, it is possible to use `read()/recv()` or `write()/send()` functions with no `poll()` (or equivalent), and your server wouldn't be blocking. But it would consume more system resources. Thus, if you try to `read()/recv()` or `write()/send()` in any file descriptor without using `poll()` (or equivalent), your grade will be 0.

* Several IRC clients exist. You have to choose one of them as a reference. Your reference client will be used during the evaluation process.
* Your reference client must be able to connect to your server without encountering any error.
* Communication between client and server has to be done via TCP/IP (v4 or v6).
* Using your reference client with your server must be similar to using it with any official IRC server. However, you only have to implement the following features:
  * You must be able to authenticate, set a nickname, a username, join a channel, send and receive private messages using your reference client.
  * All the messages sent from one client to a channel have to be forwarded to every other client that joined the channel.
  * You must have operators and regular users.
  * Then, you have to implement the commands that are specific to operators.

* Of course, you are expected to write a clean code.

## Contributors

* Salih Burak Çoşkun: [https://github.com/csalihburak/](https://github.com/csalihburak/)
* Eyüp Güler: [https://
