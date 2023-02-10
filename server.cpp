#include "server.hpp"

Server::Server(const char *port, const char *pass)
{
    this->port = std::atoi(port);
    this->password = pass;
    this->serv_soc = createSocket();
}

Server::~Server() {}

int Server::createSocket()
{

    int soc = socket(AF_INET, SOCK_STREAM, 0);
    if (soc < 0)
    {
        cout << "Error while creating socket";
        exit(-1);
    }
    int opt = 1;
    if (setsockopt(soc, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
    {
        cout << "Error while setting socket options";
        exit(-1);
    }
    if (fcntl(soc, F_SETFL, O_NONBLOCK) < 0)
    {
        cout << "Error while setting socket flag options";
        exit(-1);
    }
    struct sockaddr_in server = {};
    server.sin_family = AF_INET;
    server.sin_port = htons(this->port);
    server.sin_addr.s_addr = INADDR_ANY; // my machine address
    memset(&server.sin_zero, 0, 8);
    if (bind(soc, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        cout << "Error while binding socket." << endl;
        exit(-1);
    }
    if (listen(soc, 100) < 0)
    {
        cout << "Error while starting to listening on socket." << endl;
        exit(-1);
    }
    return soc;
}

void Server::startServer()
{
    pollfd server_fd = {serv_soc, POLLIN, 0}; // fd, requested events, returned events
    this->socket_poll.push_back(server_fd);
    cout << "Server listening on port: " << port << endl;
    while (1)
    {
        if (poll(this->socket_poll.data(), this->socket_poll.size(), -1) < 0)
        { // waits until there is something on the poll
            cout << "There was an error while polling";
        }
        for (poll_iterator it = this->socket_poll.begin(); it != this->socket_poll.end(); it++)
        {

            if (it->revents == 0)
                continue;

            if ((it->revents & POLLHUP) == POLLHUP)
            {
                cout << "client disconneted" << endl;
                close(it->fd);
            }
            if ((it->revents & POLLIN) == POLLIN)
            {
                if (it->fd == this->serv_soc)
                {
                    cout << "A client connected" << endl;
                    newClient();
                    break;
                }
                newMessage(it->fd);
            }
        }
    }
}

void Server::newClient()
{
    int cliId;
    sockaddr_in tmp = {
        0,
    };
    socklen_t len = sizeof(tmp);

    cliId = accept(serv_soc, (sockaddr *)&tmp, &len);
    if (cliId < 0)
    {
        std::cerr << "There was an error while accepting new client" << endl;
        exit(-1);
    }
    char hostname[NI_MAXHOST];
    getnameinfo((struct sockaddr *)&tmp, sizeof(tmp), hostname, NI_MAXHOST, NULL, 0, NI_NUMERICSERV);
    in_port_t port = tmp.sin_port;

    pollfd newfd = {cliId, POLLIN, 0};
    socket_poll.push_back(newfd);
    Client *newCli = new Client(cliId);
    clients.insert(std::make_pair(cliId, newCli));
}

vector<string> parse(string &msg) {
    std::istringstream ss(msg);
    std::string word;
    std::vector<std::string> words;
    while (std::getline(ss, word, ' '))
        words.push_back(word);
    return words;
}

void Server::newMessage(int soc)
{
    string tmp;
    char buffer[1000];
    Client *cli;
    cli = clients[soc];
    while (true && !strchr(buffer, '\n'))
    {
        bzero(buffer, 1000);
        int bytes = recv(soc, buffer, 1000, 0);
        if (bytes <= 0)
            break;
        tmp.append(buffer);
    }
    vector<string> words = parse(tmp);
    if (words.size() == 0) {
        return;
    }
    if (words[0] == "NICK" || words[0] == "nick") {
        cout << "'" << words[1] << "'" << endl;
        cli->nickName = words[1];
    }
    if (words[0] == ("PRIVMSG") || words[0] == ("privmsg")) {
        for (client_iterator it = clients.begin(); it != clients.end(); it++)
        {
            if (it->second->nickName == words[1])
                cout << "len: " << send(it->second->soc_fd, tmp.c_str(), tmp.length(), 0) << endl;
        }
    }
    else if (words[0] == ("JOIN") || words[0] == ("join")) {
        if (words[1].find("#") != -1)
            words[1] = (words[1].c_str() + 1);
        else {
            channel_iterator it;
            for (it = channels.begin(); it != channels.end(); it++) {
                if (it->channelName == words[1]) {
                    if (it->password == words[2]) {
                        it->users.push_back(*cli);
                        break;
                    }
                    else
                        send(soc, "Yor password is wrong!", 23, 0);
                }
            }
            if (it == channels.end()) {
                if (words[2].empty()) {
                    Channel newchannel(words[1], *cli);
                    channels.push_back(newchannel);
                }
                else {
                    Channel newchannel(words[1], words[2], *cli);
                    channels.push_back(newchannel);
                }
            }
        }
    }
    if (words[0] == "LIST\n") {
        client_iterator it;
        for (it = clients.begin(); it != clients.end(); it++) {
            cout << "'" << it->second->nickName << "'" << endl;
        }
    }
    words.clear();

}