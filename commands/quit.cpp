#include "Command.hpp"

void Command::quit(int soc, Server &serv) {
    Client *cli;
    vector<string> usrChnls;
    vector<Channel*> allChannels;
    string cmd;
    Server::poll_iterator it;
    Server::channel_iterator ct;
    Server::client_iterator cit;
    Channel::chnlUsersit tic;

    cli = (serv.getClients())[soc];
    if (cli != NULL) {
        usrChnls = cli->getChannels();
        allChannels = serv.getChannel();
        for(it = serv.getPoll().begin(); it != serv.getPoll().end(); it++) {
            if (it->fd == soc)
                break;
        }
        if (it != serv.getPoll().end()) {
            serv.getPoll().erase(it);
            cmd = "PART";
            for(ct = allChannels.begin(); ct != allChannels.end(); ct++) {
                if (std::find(usrChnls.begin(), usrChnls.end(), (*ct)->channelName) != usrChnls.end()) {
                    serv.notifyAll((*ct), (*(serv.getClients())[soc]), cmd);
                    for(tic = (*ct)->users.begin(); tic != (*ct)->users.end(); tic++) {
                        if (cli->nickName != (*tic).first->nickName)
                            (*ct)->users.erase(tic);
                    }
                }
            }
            close(cli->soc_fd);
        }
    }
}