#include "Command.hpp"

void    Command::kickMessage(Channel const *chnl, Client &cli, string name) {
    map<Client*, int> all_users;
    Channel::chnlUsersit it;
    string message;
    (void)cli;
    (void)name;

    all_users = chnl->users;
    for(it = all_users.begin(); it != all_users.end(); it++) {
        message = ":" + cli.nickName + " KICK " + chnl->channelName + " " + name + " :" + "KICKED\r\n";
        (*it).first->write(message);
    }
}

void    Command::kick(vector<string> &words, Server &serv, Client &cli) {
    Server::channel_iterator it;
    vector<Channel*> allChannels;
    Channel::chnlUsersit cit;
    string cmd;

    allChannels = serv.getChannel();
    //admin kontrol
    for (it = allChannels.begin(); it != allChannels.end(); it++) {
        if ((*it)->channelName == words[1]) {
            cout << "channelFound" << endl;
            for(cit = (*it)->users.begin(); cit != (*it)->users.end(); cit++) {
                if (words[2] == (*cit).first->nickName) {
                    kickMessage((*it), cli, (*cit).first->nickName);
                }
            }
        }
    }
}