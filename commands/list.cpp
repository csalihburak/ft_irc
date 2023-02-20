#include "Command.hpp"

void Command::list(vector<string> &words, Server &serv) {
    string message;
    vector<Channel*> allChannel;
    Server::channel_iterator it;
    Client *cli = serv.getClient();
    (void)words;

    allChannel = serv.getChannel();
    if (!allChannel.empty()) {
        for(it = allChannel.begin(); it != allChannel.end(); it++) {
            std::stringstream ss;
            ss << ((*it)->users).size();
           message = ":localhost 322 " + cli->nickName + " " + ((*it)->channelName) + " " + ss.str() + " :" + "\r\n";
            cli->write(message);
        }
    } else {
        message = ":ircserv 411 " + cli->nickName + " :There is no channel on the server!\r\n";
        cli->write(message);
    }
}