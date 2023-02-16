#include "Command.hpp"

void Command::list(vector<string> &words, Server &serv) {
    string message;
    vector<Channel*> allChannel;
    Server::channel_iterator it;
    Client *cli = serv.getClient();
    (void)words;

    //:<server-name> 322 <your-nickname> <channel-name> <num-users> :<topic>
    allChannel = serv.getChannel();
    if (!allChannel.empty()) {
        for(it = allChannel.begin(); it != allChannel.end(); it++) {
           message = ":localhost 322 " + cli->nickName + " " + ((*it)->channelName) + " " + std::to_string(((*it)->users).size()) + " :" + "\r\n";
            cli->write(message);
        }
    } else {
        message = ":ircserv 411 " + cli->nickName + " :There is no channel on the server!\r\n";
        cli->write(message);
    }
}