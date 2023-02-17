#include "Command.hpp"

string Command::join(vector<string>& words, Server &serv) {

    string message;
    Channel *channel = NULL;
    vector<Channel*> allChannels;
    Server::channel_iterator it;
    Client *cli = serv.getClient();

    allChannels = serv.getChannel();

    if ((int)words[1].find("#") != 0 || (int)words[1].find(" ") != -1 || (int)words[1].find("-") != -1) {
        message = "475 " + cli->nickName + " :Cannot join channel\r\n";
        cli->write(message);
        return ("");
    }
    for (it = allChannels.begin(); it != allChannels.end(); it++) {
        if ((*it)->channelName == words[1]) {
            cli->channels.push_back(words[1]);
            if (std::find((*it)->users.begin(), (*it)->users.end(), cli) == (*it)->users.end())
                (*it)->users.push_back(cli);
            channel = *it;
        }
    }
    if (channel == NULL) {
        cli->channels.push_back(words[1]);
        Channel *newchannel = new Channel(words[1], cli);
        channel = newchannel;
        serv.addChannel(words[1], *cli);
    }
    for (unsigned long i = 0; i < channel->users.size(); i++) {
        message =  ":" + cli->getPrefix() + " JOIN " + words[1] + "\r\n";
        channel->users[i]->write(message);
    }
    message.clear();
    if (channel->users.size() == 1)
        message = ":ircserv 331 " + cli->nickName + " " + channel->channelName + ":Topic is not set\r\n";
    message.append(":ircserv 353 " + cli->nickName + " = " + channel->channelName + " :@");
    for (unsigned long  i = 0; i < channel->users.size(); i++) {
        message.append(channel->users[i]->nickName);
        if (i + 1 == channel->users.size())
            message.append("\r\n");
        else
            message.append(" ");
    }
    message.append(":ircserv 366 " + cli->nickName + " " + channel->channelName + " End of /NAMES list\r\n");
    cli->write(message);
    return (words[1]);
}
