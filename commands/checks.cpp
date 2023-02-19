#include "Command.hpp"

int Command::checks(Server &serv, vector<string> &words, Client &cli)
{
    map<int, Client*> allClients;
    string message;


    allClients =  serv.getClients();
    Server::client_iterator it;
    if (cli.is_avl == 2) {
        if (words[0] == serv.getPassword()) {
            cli.write(welcomemsg());
            cli.is_avl = 1;
        } else {
            message = ":ircserv 404 " + cli.nickName + " " + "wrong password\r\n";
            cli.write(message);
        }
    } else if (cli.is_avl == 0) {
        if (serv.getPassword() == words[0]) {
            cli.is_avl = 1;
            cli.pass = words[0];
            cli.write(welcomemsg());
            cli.write(":ircserv 401 Please provide a nickname: ");
        } else {
            cli.write(":ircserv 404 wrong password! Try again!!\r\n");
        }
    } else if (cli.nickName.empty()) {
        if (allClients.size() > 1) {
            for (it = allClients.begin(); it != allClients.end(); it++) {
                if ((it)->second->nickName == words[0]) {
                    cli.write(":ircserv 404 This nickname already exists!\r\n");
                    cli.write(":ircserv 401 Please provide a unique nickname: ");
                    return (0);
                }
            }
        }
        cli.nickName = words[0];
        cli.write(":ircserv 401 Please provide a username: ");
    } else if (cli.userName.empty()) {
        if (cli.nickName != words[0])
            cli.userName = words[0];
        else {
            cli.write(":ircserv 404 Cannot be the same!\n");
            cli.write(":ircserv 401 Please provide a username: ");
        }
    }
    return 1;
}