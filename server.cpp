#include "server.hpp"


Server::Server(const char *port, const char *pass) {
    this->port = std::atoi(port);
    this->password = pass;
    this->serv_soc = createSocket();
}

Server::~Server() {}

int Server::createSocket() {

    int soc = socket(AF_INET, SOCK_STREAM, 0);
    if (soc < 0) {
        cout << "Error while creating socket";
        exit(-1);
    }
    int opt = 1;
    if (setsockopt(soc, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        cout << "Error while setting socket options";
        exit(-1);
    }
    if (fcntl(soc, F_SETFL, O_NONBLOCK) < 0) {
        cout << "Error while setting socket flag options";
        exit(-1);
    }
    struct sockaddr_in server = {};
    server.sin_family = AF_INET;
    server.sin_port = htons(this->port);
    server.sin_addr.s_addr = INADDR_ANY; // my machine address
    memset(&server.sin_zero, 0, 8);
    if (bind(soc, (struct sockaddr *) &server, sizeof(server)) < 0) {
        cout << "Error while binding socket." << endl;
        exit(-1);
    }
    if (listen(soc, 100) < 0) {
		cout << "Error while starting to listening on socket." << endl;
        exit(-1);
    }
    return soc;
}

void Server::startServer() {
    pollfd server_fd = {serv_soc, POLLIN, 0}; //fd, requested events, returned events
    this->socket_poll.push_back(server_fd);
    cout << "Server listening on port: " << port << endl;
    while (1) {
        if (poll(this->socket_poll.begin().base(), this->socket_poll.size(), -1) < 0) { // waits until there is something on the poll
            cout << "There was an error while polling";
        }
        for (poll_iterator it = this->socket_poll.begin(); it != this->socket_poll.end(); it++) {
            
            if ((it->revents & POLLHUP) == POLLHUP) {
                cout << "client disconneted" << endl;
                    close(it->fd);
            }
            if ((it->revents & POLLIN) == POLLIN) {
                if (it->fd == this->serv_soc) {
                    cout << "A client connected" << endl;
                    newClient();
                    break;
                }
/*                 char buffer[100]; for messages
	            bzero(buffer, 100);
                recv(it->fd, buffer, 100, 0);
                cout << buffer << endl;
                sprintf(buffer, "Hoş geldin len %d\n", it->fd);
                send(it->fd, buffer, strlen(buffer), 0); */
            }
        }
    }
}

void Server::newClient() {
    int cliId;
    sockaddr_in tmp = {0,};
    socklen_t len = sizeof(tmp);
    
    cliId = accept(serv_soc, (sockaddr *)&tmp, &len);
    if (cliId < 0) {
        std::cerr << "There was an error while accepting new client" << endl;
        exit(-1);
    }

    pollfd newfd = {cliId, POLLIN, 0};
    socket_poll.push_back(newfd);
    char hostname[1025];
    if (getnameinfo((struct sockaddr*)&tmp, len, hostname, 1025, NULL, 0, NI_NUMERICSERV) != 0) {
        std::cerr << "There was an error while getting the hostname" << endl;
        exit(-1);
    }
    cout << hostname << "  " << ntohs(tmp.sin_port) << endl;



}