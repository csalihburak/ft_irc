#include "Command.hpp"


void Command::ison(vector<string>&words, Client &cli, Server &serv) {
    map<int, Client*> allClients;
    string names;
    string message;
    Server::client_iterator cit;

    message = ":irc.localhost 303 " + cli.nickName + " :";
    allClients = serv.getClients();
    for (cit = allClients.begin(); cit != allClients.end(); cit++) {
        for (unsigned long i = 1; i < words.size(); i++) {
            if ((*cit).second->nickName == words[i])
                names.append(words[i] + " ");
        }
    }
    message.append("agunes");
    message.append(names + "\r\n");
    cli.write(message);
}