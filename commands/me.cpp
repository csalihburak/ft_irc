#include "Command.hpp"

void Command::me(Client &cli) {
    string nick = "Nickname: " + cli.nickName;
    string username = "Username: " + cli.userName;
    vector<string> channels = cli.channels;
    string cha = "channels: ";
    for (unsigned long i = 0; i < channels.size(); i++) {
        cha.append(channels[i] + " ");
    }
    string message = ":agunes!~agunes@localhost PRIVMSG "+  cli.nickName + " :" +  nick + " || "  + username +  " || " + cha + "\r\n";
    cli.write(message);
}

void Command::whois(vector<string> &words, Client &cli, Server &serv) {
    (void)words;
    map<int, Client *> clients = serv.getClients();
    Server::client_iterator it;
    string users;
    for (it = clients.begin(); it != clients.end(); it++) {
        users.append((it)->second->nickName);
        users.append(" ");
    }
    cout << users << endl;
    string message = ":agunes!~agunes@localhost PRIVMSG "+  cli.nickName + " :Available users on the server: " + users + "\r\n";
    cli.write(message);
}