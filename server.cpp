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


void Server::notifyAll(Channel const *chnl, Client &cli, string &cmd) {
    map<Client*, int> all_users;
    Channel::chnlUsersit it;
    string message;

    all_users = chnl->users;
    for (it = all_users.begin(); it != all_users.end(); it++) {
        if ((it)->first->nickName != cli.nickName) {
            message = "* " + cli.nickName + " has quit (" + cmd + ")\r\n";
            (it)->first->write(message);
        }
    }
}

void Server::startServer(Server &serv)
{
    pollfd server_fd = {serv_soc, POLLIN, 0};
    this->socket_poll.push_back(server_fd);
    vector<string> buff;
    cout << "Server listening on port: " << port << endl;
    while (1)
    {
        if (poll(this->socket_poll.data(), this->socket_poll.size(), -1) < 0) { // waits until there is something on the poll
            cout << "There was an error while polling";
        }
        for (poll_iterator it = this->socket_poll.begin(); it != this->socket_poll.end(); it++) {

            if (it->revents == 0)
                continue;

            if ((it->revents & POLLHUP) == POLLHUP) {
                cout << "client disconneted" << endl;
                buff.push_back("client disconneted");
                Command::quit(it->fd, serv, buff);
                //delete clients[it->fd];
                //clients.erase(it->fd);
                break;
            }
            if ((it->revents & POLLIN) == POLLIN) {
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


void Server::newClient() {
    int cliId;
    sockaddr_in tmp;
    socklen_t len;
    
    len = sizeof(tmp);
    cliId = accept(serv_soc, (sockaddr *)&tmp, &len);
    if (cliId < 0) {
        std::cerr << "There was an error while accepting new client" << endl;
        exit(-1);
    }
    pollfd newfd = {cliId, POLLIN, 0};
    socket_poll.push_back(newfd);
    Client *newCli = new Client(cliId);
    newCli->flag = 1;
    string s = ":ircserv 001 :Welcome to ft_irc server!\r\nPlease enter the password: \r\n";
    newCli->write(s);
    clients.insert(std::make_pair(cliId, newCli));
}


Channel &Server::getChannel(string &name) {
    unsigned long i;

    for (i = 0; i < channels.size(); i++) {
        if (channels[i]->channelName == name)
            return *channels[i];
    }
    return(*channels[i]);
}

void Server::newMessage(int soc) {
    string tmp;
    char buffer[1000];
    this->tmp_fd = soc;
    while (true) {
        bzero(buffer, 1000);
        int bytes = recv(soc, buffer, 1000, 0);
        tmp.append(buffer);
        if (bytes <= 0 || strchr(buffer, '\n') || strchr(buffer, '\r'))
            break;
    }
	if (tmp.length() < 3)
        return;
    Command cmd(tmp);
    cmd.parse(*this);
    return;
}