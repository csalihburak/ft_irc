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

int Command::kickCont(vector<string> &words, Server &serv, Client &cli) {
    Channel::chnlUsersit    it;
    vector<Channel*> allChannels;
    Server::channel_iterator    et;
    (void)words;

    allChannels = serv.getChannel();
    for (et = allChannels.begin(); et != allChannels.end(); et++) {
        if ((*et)->channelName == words[1]) {
            for(it = (*et)->users.begin(); it != (*et)->users.end(); it++) {
                if (cli.nickName == (*it).first->nickName) {
                    if ((*it).second) {
                        return (1);
                    } else {
                        cli.write("403 " + cli.nickName + " :You're not channel operator\r\n");
                        return (0);
                    }
                }
            }
        }
    }
    if (et == allChannels.end())
        cli.write(":ircserv 403 " + cli.nickName + " " + words[1] + " :No such channel\r\n");
    return (0);
}

void    Command::kick(vector<string> &words, Server &serv, Client &cli) {
    Server::channel_iterator it;
    vector<Channel*> allChannels;
    Channel::chnlUsersit cit;

    allChannels = serv.getChannel();
    if (kickCont(words, serv, cli)) {
        for (it = allChannels.begin(); it != allChannels.end(); it++) {
            if ((*it)->channelName == words[1]) {
                for(cit = (*it)->users.begin(); cit != (*it)->users.end(); cit++) {
                    if (words[2] == (*cit).first->nickName) {
                        kickMessage((*it), cli, (*cit).first->nickName);
                        (*it)->users.erase(cit);
                        return ;
                    }
                }
                if (cit == (*it)->users.end()) {
                    cli.write(":ircserv 404 " + cli.nickName + " " + words[1] + " :User not in the channel!\r\n");
                    return ;
                }
            }
        }
    }
}