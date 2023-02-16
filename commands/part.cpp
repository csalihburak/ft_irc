#include "Command.hpp"

void Command::part(vector<string>& words, Server &serv, Client &cli) {
    vector<Channel*> allChannels;
    vector<Client*>::iterator it;
    vector<string> usrChnls;
    string message;
    string cmd;
    Server::channel_iterator ct;

    usrChnls = cli.getChannels();
    allChannels = serv.getChannel();
    cmd = "PART";

    for (ct = allChannels.begin(); it != allChannels.end(); ct++) {
        if ((*ct)->channelName == words[1])
            break;
    }
    if (ct == allChannels.end()) {
        message = cli.nickName + " " + words[1] + " :You're not on that channel";
        cli.write(message);
    } else {
        if (std::find((*ct)->users.begin(), (*ct)->users.end(), &cli) != (*ct)->users.end()) {


        for(ct = allChannels.begin(); ct != allChannels.end(); ct++) {
            if (std::find(usrChnls.begin(), usrChnls.end(), (*ct)->channelName) != usrChnls.end()) {
                for (it = (*ct)->users.begin(); it != (*ct)->users.end(); it++) {
                    message =  ":" + cli.nickName + "!~" + cli.userName + "@localhost PART " + (*ct)->channelName + " :(Disconnected)\r\n";
                    cout << message << endl;
                    (*it)->write(message);
                }
                (*ct)->users.erase(std::find((*ct)->users.begin(), (*ct)->users.end(), &cli));
                break;
            }
        }
    }

}