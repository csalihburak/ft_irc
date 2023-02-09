#include "client.hpp"

Client::Client(int fd) {
    this->soc_fd = fd;
}

Client::~Client() {}