#include "Command.hpp"

string Command::join(vector<string>& words, Server &serv, Client &cli) {

    string message;
    Channel *channel;
    vector<string> usrChnls;
    vector<Channel*> allChannels;
    Server::channel_iterator it;
    Channel::chnlUsersit cit;

    allChannels = serv.getChannel();
    channel = NULL;
    usrChnls = cli.getChannels();
    if ((int)words[1].find("#") != 0 || (int)words[1].find(" ") != -1 || (int)words[1].find("-") != -1) {
        message = "475 " + cli.nickName + " :Cannot join channel\r\n";
        cli.write(message);
        return ("");
    }
    if (allChannels.size() > 0) {
        for (it = allChannels.begin(); it != allChannels.end(); it++) {
            if ((*it)->channelName == words[1]) { 
				if (std::find((*it)->bannedUsrs.begin(), (*it)->bannedUsrs.end(), cli.nickName) != (*it)->bannedUsrs.end()) {
                	message = ":ircserv 474 " + cli.nickName + " " + (*it)->channelName + " :Cannot join channel (+b)\r\n";
					cli.write(message);
					return (words[0]);
                }
                if (std::find(usrChnls.begin(), usrChnls.end(), (*it)->channelName) != usrChnls.end()) {
                    message = ":ircserv 443 " + (*it)->channelName + " " + cli.nickName +  " :is already on channel\r\n";
                    cli.write(message);
                    return words[0];
                }
            }
        }
        for (it = allChannels.begin(); it != allChannels.end(); it++) {
            if ((*it)->channelName == words[1]) {
                cli.channels.push_back(words[1]);
                for (cit = (*it)->users.begin(); cit != (*it)->users.end(); cit++) {
                    if ((cit)->first->nickName != cli.nickName)
                    (*it)->users.insert(std::make_pair(&cli, 0));
                }
                channel = *it;
            }
        }
    }
    if (channel == NULL) {
        cli.channels.push_back(words[1]);
        Channel *newchannel = new Channel(words[1], cli);
        channel = newchannel;
        serv.getChannel().push_back(newchannel);
    } else if (channel->users.size() == 0) {
        channel->users.insert(std::make_pair(&cli, 1));
    }
    for (cit = channel->users.begin(); cit !=  channel->users.end(); cit++) {
        message =  ":" + cli.getPrefix() + " JOIN " + words[1] + "\r\n";
        (cit)->first->write(message);
    }
    message.clear();
    if (channel->topic.empty())
        message = ":ircserv 331 " + cli.nickName + " " + channel->channelName + " :Topic is not set\r\n";
    else
        message = ":ircserv 332 " + cli.nickName + " " + channel->channelName + " :" + channel->topic + "\r\n";
    message.append(":ircserv 353 " + cli.nickName + " = " + channel->channelName + " :@");
    for (cit = channel->users.begin(); cit !=  channel->users.end();) {
        message.append((cit)->first->nickName);
        if (++cit == channel->users.end())
            message.append("\r\n");
        else
            message.append(" ");
    }
    message.append(":ircserv 366 " + cli.nickName + " " + channel->channelName + " End of /NAMES list\r\n");
    cli.write(message);
    return (words[1]);
}
