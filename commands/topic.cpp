#include "Command.hpp"
void Command::topic(vector<string> &words, Client &cli, Server &serv)
{
    vector<Channel *> allChannels;
    Server::channel_iterator ct;
    Channel::chnlUsersit userit;
    allChannels = serv.getChannel();
    for (ct = allChannels.begin(); ct != allChannels.end(); ct++) {
        if ((*ct)->channelName == words[1]){
            if (words[2].find(":") != std::string::npos) {
                for (userit = (*ct)->users.begin(); userit != (*ct)->users.end(); userit++)
                    if ((*userit).first->nickName == cli.nickName) {
                        if((*userit).second == 1) {
                            (*ct)->topic = words[2];
                            for (userit = (*ct)->users.begin(); userit != (*ct)->users.end(); userit++) {
                                (*userit).first->write(":ircserv 332 " + cli.nickName + " " + (*ct)->channelName + " " + (*ct)->topic  + "\r\n");
                            }
                            return;
                        }
                        else
                            cli.write(":ircserv 403 " + cli.nickName + ":You're not a channel operator\r\n");
                    }
            }
            else
                cli.write(":ircserv 332 " + cli.nickName + " " + (*ct)->channelName + " :" + words[2] + "\r\n");
        }
    }
}