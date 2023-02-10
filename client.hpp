#pragma once

#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <poll.h>
#include <iostream>
#include <unistd.h>
#include <cstdio>


using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::map;


class Client {
    public:
        std::string nickName;
        std::string pass;
        int soc_fd;
        
        Client();
        Client(int);
        
        ~Client();
        

};