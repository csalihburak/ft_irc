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
		Client *admin;
        vector<Client *> users;
        std::string password;

		Channel(Channel const&);
		Channel &operator=(Channel const &x);
		Channel();
		Channel(std::string, Client*);
		~Channel();

};