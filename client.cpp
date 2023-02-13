#include "client.hpp"


Client::Client() {
    
}

Client::Client(int fd) {
    this->soc_fd = fd;
}

std::string Client::getPrefix() const {
	return nickName + (userName.empty() ? "" : "!" + userName) + ("@127.0.0.1");
}

Client::~Client() {}


void Client::write(const string &msg) {
    if (send(soc_fd, msg.c_str(), msg.length(), 0) < 0)
        std::cerr << "Error while sending self message!" << endl;
}