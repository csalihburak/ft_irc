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


using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::map;


class Client {
    public:
        string nickName;
        string userName;
        string pass;
        vector<string> channels;
        int mod;
        int soc_fd;
		int is_avl;
        int flag;
        
        Client();
        Client(int);
        Client(Client const&);
        ~Client();

        Client &operator=(Client const &x); 
        void write(const string &);
        string getPrefix() const;
		int isAvailable();
        vector<string> &getChannels();

        

};