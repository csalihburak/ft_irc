#pragma once

#include <sys/poll.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <algorithm>
#include <string.h>
#include <vector>
#include <map>
#include <poll.h>
#include <iostream>
#include <unistd.h>
#include <cstdio>

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::map;


class Server {
	private:
		int				serv_soc;
		int				port;
		string			password;
		vector<pollfd>	socket_poll;
		typedef vector<pollfd>::iterator poll_iterator;
	public:
		Server(const char *port, const char *password);
		~Server();
		int createSocket();
		void startServer();
		void newClient();
};