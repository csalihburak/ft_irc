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
		Client admin;
        vector<Client> users;
        std::string password;
	
		Channel();
		Channel(std::string, Client);
		Channel(std::string, std::string, Client);
		~Channel();

};