#include "client.hpp"


Client::Client() {
    
}

Client::Client(int fd) {
    this->soc_fd = fd;
    this->is_avl = 0;
}

Client::Client(Client const &x) {
    *this = x;
}

Client &Client::operator=(Client const &x) {
    if (this == &x)
        return(*this);
    return (*this);
}

int Client::isAvailable() {return is_avl;}

std::string Client::getPrefix() const {
	return this->nickName + ("!" + this->userName) + ("@localhost");
}

Client::~Client() {}


void Client::write(const string &msg) {
    if (send(soc_fd, msg.c_str(), msg.length(), 0) < 0)
        std::cerr << "Error while sending self message!" << endl;
}

vector<string> &Client::getChannels() {
    return channels;
}