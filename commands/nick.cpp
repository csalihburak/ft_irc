#include "Command.hpp"

void Command::nick(vector<string> &words, Client &cli, Server &serv) {
    string rep;
    map<int, Client*> allClients;
    Server::client_iterator cit;

    if (words[1].empty()) {
        rep = ":ircserv 431 " + cli.nickName + " :No nickname is given!";
        cli.write(rep);
    } else {
        allClients = serv.getClients();
        for (cit = allClients.begin(); cit != allClients.end(); cit++) {
            if ((cli.soc_fd != cit->second->soc_fd) && cit->second->nickName == words[1]) {
                rep = ":ircserv 433 " + cli.nickName + " " + words[1] + " :Nickname is already in use";
                cli.write(rep);
                break;;
            }
        }
        if (cit == allClients.end()) {
            rep = ":" + cli.getPrefix() + " NICK " + words[1] + "\r\n";
            cli.nickName = words[1];
            cli.write(rep);
        }
    }
    
}