#include "channel.hpp"

Channel::Channel() {
	this->channelName = "channelName";
	this->password = "";
}

Channel::Channel(std::string name, Client &admin) {
    this->admin = std::make_pair(&admin, 1);
    this->channelName = name;
    users.insert(std::make_pair(&admin, 1));
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
