IRC Server Project
Description
This project is an IRC server implemented in C++98. It can handle multiple clients at the same time and supports the following features:

Authentication
Setting a nickname and username
Joining a channel
Sending and receiving private messages
Broadcasting channel messages to all clients who have joined the channel
User types: operators and regular users
Operator-specific commands
Contributors
Salih Burak Çoşkun: https://github.com/csalihburak/
Eyüp Güler: https://github.com/egulerr
Mert Alaşahan: https://github.com/Mertflixs/
Requirements
The server must be non-blocking and handle all I/O operations in a non-blocking way.
Only one poll() (or equivalent) can be used for handling all I/O operations.
Forking is not allowed.
Communication between client and server has to be done via TCP/IP (v4 or v6).
The server must support authentication, setting a nickname and username, joining a channel, sending and receiving private messages, and broadcasting channel messages to all clients who have joined the channel.
The server must support two types of users: operators and regular users.
The server must implement operator-specific commands.
Installation
To install and run the IRC server, follow these steps:

Clone the repository:
shell
Copy code
$ git clone https://github.com/[USERNAME]/ircserv.git
Compile the server using the Makefile:
go
Copy code
$ make
Run the server:
php
Copy code
$ ./ircserv <port> <password>
Files
Makefile: Compiles the server
*.h, *.hpp, *.cpp, *.tpp, *.ipp: Header, source, and template files
config: Optional configuration file
Usage
To use the IRC server, follow these steps:

Connect to the server using an IRC client.
Authenticate using the password specified when starting the server.
Set a nickname and username.
Join a channel.
Send and receive private messages.
Broadcast messages to all clients who have joined the channel.
Use operator-specific commands if you are an operator
