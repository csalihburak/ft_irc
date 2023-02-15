#include "channel.hpp"

Channel::Channel() {
	this->admin = nullptr;
	this->channelName = "";
	this->password = "";
}

Channel::Channel(std::string name, Client *admin) {
    this->admin = admin;
    this->channelName = name;
    users.push_back(admin);
}


Channel::Channel(Channel const &x) {
    *this = x;
}

Channel &Channel::operator=(Channel const &x) {
    if (this == &x)
        return(*this);
    return (*this);
}


Channel::~Channel() {}