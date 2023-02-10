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
#include <sstream>
#include <poll.h>
#include <iostream>
#include <unistd.h>
#include <cstdio>
#include <functional> 
#include <cctype>
#include <locale>

#include "channel.hpp"
#include "client.hpp"

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::map;


class Channel;
class Client;

class Server {
	private:
		int				serv_soc;
		int				port;
		string			password;
		vector<pollfd>	socket_poll;
		vector<Channel> channels;
		map<int, Client *> clients;
		typedef vector<Channel>::iterator channel_iterator;
		typedef vector<pollfd>::iterator poll_iterator;
		typedef map<int, Client*>::iterator client_iterator;
	public:
		Server(const char *port, const char *password);
		~Server();
		int createSocket();
		void startServer();
		void newClient();
		void newMessage(int);
};