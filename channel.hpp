#pragma once 

#include "client.hpp"

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::map;

class Client;

class Channel {
    public:
        std::string channelName;
		std::pair<Client *, int> admin;
        map<Client *, int> users;
		vector<string> bannedUsrs;
		string topic;
        std::string password;
		typedef map<Client *, int>::iterator chnlUsersit;

		Channel(Channel const&);
		Channel &operator=(Channel const &x);
		Channel();
		Channel(std::string, Client&);
		~Channel();
};