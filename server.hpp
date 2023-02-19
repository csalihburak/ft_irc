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
#include <csignal>
#include <iostream>
#include <unistd.h>
#include <cstdio>
#include <functional> 
#include <cctype>
#include <locale>

#include "channel.hpp"
#include "client.hpp"
#include "commands/Command.hpp"

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::map;


# define RESET "\e[0m"
# define RED "\e[1;91m"
# define CYAN "\e[1;36m"
# define YELLOW "\e[1;33m"
# define PURPLE "\e[1;35m"


class Channel;
class Client;

class Server {
	private:
		int				serv_soc;
		int				port;
		int				tmp_fd;
		string			password;
		vector<pollfd>	socket_poll;
		vector<Channel*> channels;
		map<int, Client *> clients;
	public:
		typedef vector<Channel*>::iterator channel_iterator;
		typedef vector<pollfd>::iterator poll_iterator;
		typedef map<int, Client*>::iterator client_iterator;
		Server(const char *port, const char *password);
		~Server();
		Client *getClient() {return clients[tmp_fd];}
		map<int, Client *>& getClients() { return clients; }
		vector<Channel*> &getChannel() {return channels;}
		vector<pollfd> &getPoll() { return socket_poll;}
		Channel &getChannel(string &);
		int createSocket();
		void startServer(Server &);
		void newClient();
		void newMessage(int);
		void notifyAll(Channel const *, Client &, string &);
		string getPassword() { return password;}
};
