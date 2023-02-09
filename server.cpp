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
            
            if (it->revents == 0)
                continue;

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
                newMessage(it->fd);
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
    //string response = "HTTP/1.1 101 Switching Protocols\nUpgrade: websocket\nConnection: Upgrade\nSec-WebSocket-Accept: RAFRY/6VKUrYnUQ7d9sjnQ==\nSec-WebSocket-Protocol: text.ircv3.net";
    send(cliId, "200", 3, 0);
    pollfd newfd = {cliId, POLLIN, 0};
    socket_poll.push_back(newfd);
    clients.push_back(cliId);
    
}

void Server::newMessage(int soc) {
    string tmp;
    cout << soc << endl;
    char buffer[2];
    while (true && (!strchr(buffer, '\n') && !strchr(buffer, 4))) {
        bzero(buffer, 2);
        int bytes = recv(soc, buffer, 2, 0);
        if (bytes <= 0)
            break;
        tmp.append(buffer);
    }
    for (clients_iterator it = clients.begin(); it != clients.end(); it++)
        if (*it != soc)
            send(*it, tmp.c_str(), tmp.length(), 0);
}