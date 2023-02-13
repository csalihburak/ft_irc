#include "channel.hpp"

Channel::Channel() {}

Channel::Channel(std::string name, Client admin) {
    this->admin = admin;
    this->channelName = name;
}

Channel::Channel(std::string name, std::string password, Client admin) {
    this->admin =  admin;
    this->channelName = name;
    this->password = password;
}

Channel::~Channel() {}