#include "Command.hpp"

void    Command::kickMessage(Channel const *chnl, Client &cli, string name) {
    vector<Client*> all_users;
    vector<Client*>::iterator it;
    string message;
    (void)cli;
    (void)name;

    all_users = chnl->users;
    for(it = all_users.begin(); it != all_users.end(); it++) {
        message = ":" + cli.nickName + " KICK " + chnl->channelName + " " + name + " :" + "KICKED\r\n";
        (*it)->write(message);
    }
}

void    Command::kick(vector<string> &words, Server &serv, Client &cli) {
    Server::channel_iterator it;
    vector<Channel*> allChannels;
    string cmd;

    allChannels = serv.getChannel();
    //admin kontrol
    for (it = allChannels.begin(); it != allChannels.end(); it++) {
        if ((*it)->channelName == words[1]) {
            cout << "channelFound" << endl;
            for (unsigned long i = 0; i < (*it)->users.size(); i++) {
                if (words[2] == (*it)->users[i]->nickName) {
                    kickMessage((*it), cli, (*it)->users[i]->nickName);
                }
            }
        }
    }
}