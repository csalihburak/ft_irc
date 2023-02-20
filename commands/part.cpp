#include "Command.hpp"

void Command::part(vector<string>& words, Server &serv, Client &cli) {
    vector<Channel*> allChannels;
    vector<string> usrChnls;
    string message;
    string cmd;
    Channel::chnlUsersit cit;
    Server::channel_iterator ct;
    Channel::chnlUsersit it;

    usrChnls = cli.getChannels();
    allChannels = serv.getChannel();
    cmd = "PART";

    for (ct = allChannels.begin(); ct != allChannels.end(); ct++) {
        if ((*ct)->channelName == words[1])
            break;
    }
    if (ct == allChannels.end()) {
        message = ":ircserv 403 " + cli.nickName + " " + words[1] + " :No such channel!\r\n";
        cli.write(message);
    } else {
		for(cit = (*ct)->users.begin(); cit != (*ct)->users.end(); cit++) {
            if (cli.nickName == (*cit).first->nickName)
                break;
        }
        if (cit == (*ct)->users.end()) {
            message = ":ircserv 442 " + cli.nickName + " " + words[1] +  " :You're not on that channel\r\n";
            cli.write(message);
        } else {
            for (it = (*ct)->users.begin(); it != (*ct)->users.end(); it++) {
                message =  ":" + cli.nickName + "!~" + cli.userName + "@localhost PART " + (*ct)->channelName + " :(Disconnected)\r\n";
                (*it).first->write(message);
            }
            for(cit = (*ct)->users.begin(); cit != (*ct)->users.end(); cit++) {
                if (cli.nickName == (*cit).first->nickName) {
                    (*ct)->users.erase(cit);
                    for (vector<string>::iterator x = cli.channels.begin(); x != cli.channels.end(); x++) {
                        if ((*x) == words[1]) {
                            cli.channels.erase(x);
                            break;
                        }
                    }
                    break;
                }
            }
        }
    }
}