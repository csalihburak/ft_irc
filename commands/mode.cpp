#include "Command.hpp"

void Command::mode(vector<string> &words, Client &cli, Server &serv) {
    string message;
    vector<Channel*> allChannels;
    vector<string> usrChnls;
    Channel::chnlUsersit cit;
    Channel::chnlUsersit cit2;
    Server::channel_iterator it;

    allChannels = serv.getChannel();
    usrChnls = cli.getChannels();
    for (it = allChannels.begin(); it != allChannels.end(); it++) {
        if (words[1] == (*it)->channelName)
            break;
    }
    if (it == allChannels.end()) {
        message =":ircserv 403 " + cli.nickName + " " + words[1] + " :No such channel\r\n";
        cli.write(message);
        return;
    }
    if (std::find(cli.channels.begin(), cli.channels.end(), (*it)->channelName) != cli.channels.end()) {
        for (cit = (*it)->users.begin(); cit != (*it)->users.end(); cit++) {
            if ((*cit).first->nickName == cli.nickName) {
                if ((*cit).second == 1) {
                    for(cit2 = (*it)->users.begin(); cit2 != (*it)->users.end(); cit2++) {
                        if ((*cit2).first->nickName == words[3]) {
                            if (words[2] == "+b") {
                                (*it)->bannedUsrs.push_back(words[3]);
                                message = ":" + cli.nickName + " KICK " + words[1] + " " + words[3] + " :" + "Banned from channel by " + cli.nickName + "\r\n";
                                (*cit2).first->write(message);
                                (*it)->users.erase(cit2);
                                for ((cit2) = (*it)->users.begin(); cit2 != (*it)->users.end(); cit2++) {                                        
                                    (*cit2).first->write(message);
                                }
                                return;
                            }
                            if (words[2] == "+h") {
                                message = ":ircserv 324" + words[3] + " " + words[1] + " " + words[2] + "\r\n";
                                (*cit2).second = 1;
                                cli.write(message);
                            }
                            return;
                        }
                    }
                } else {
                    cli.write("403 " + cli.nickName + " :You're not channel operator\r\n");
                    return;
                }
            }
        }
        cli.write(":ircserv 404 " + cli.nickName + " " + words[1] + " :User not in the channel!\r\n");
    }
}