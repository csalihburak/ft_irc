#pragma once

#include "server.hpp"

class Client {
    private:
    public:
        std::string nickName;
        int soc_fd;
        Client(int);
        ~Client();
        

};